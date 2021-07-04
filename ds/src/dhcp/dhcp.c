/****************************************************************************
* FILE: dhcp.c  Purpose: library for dhpc protocol impl by binary trie
*
* DEVELOPER:   Daniel Zaken				TEAM: Green
*
* REVIEWER:    Kim Aharfi				STATUS: Approved
*
****************************************************************************/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*asserts*/
#include <string.h> /* memcpy */
#include <limits.h> /*CHAR_BIT*/

#include "dhcp.h" /*my current lib*/
/****************************************************************************
*                              DEFINES
****************************************************************************/
#define FALSE 0
#define TRUE 1
#define TOTAL_BIT_NUM CHAR_BIT * BYTES_IN_IPv4
/****************************************************************************
*                         TYPEDEFS & STRUCS
****************************************************************************/
typedef struct trie_node trie_node_t;

struct dhcp
{
    trie_node_t *trie;
    unsigned int num_bits_in_subnet;
    ip_t network;
};

struct trie_node
{
	trie_node_t *child[2];
    int is_full;
};
/****************************************************************************
*                              TRIE FUNCS
****************************************************************************/
static trie_node_t *TrieCreate(status_t *status);

static void TrieDestroy(trie_node_t* root);

static trie_node_t *TrieInsert(trie_node_t *root, 
                               unsigned int *output, 
                               unsigned int height,
                               status_t *status);                         

static trie_node_t *TrieFree(trie_node_t *root,
                             unsigned int *requested_ip,
                             unsigned int height,
                             status_t *status);

static size_t TrieCount(const trie_node_t *root, unsigned int height);
/****************************************************************************
*                             UTIL FUNCS
****************************************************************************/
static trie_node_t *InitNetwork(trie_node_t *root,
                                unsigned int num_bits_in_subnet,
                                status_t *status);

static unsigned int ConvertToInt(const ip_t ip);

static void ConvertToIP(unsigned int ip, ip_t out);

static int IsInNetwork(const dhcp_t *dhcp, unsigned int requested_ip);

static trie_node_t *CreateNode(void);

static void UpdateIsFull(trie_node_t *root);
/****************************************************************************
*                             API IMPL
****************************************************************************/
dhcp_t *DHCPCreate(const ip_t network, unsigned int num_bits_in_subnet)
{
    status_t status = SUCCESS;
    dhcp_t *manage = (dhcp_t*)malloc(sizeof(dhcp_t));

    if( NULL == manage )
    {
        return NULL;
    }

    manage->trie = TrieCreate(&status);

    if( NULL == manage->trie )
    {
        free(manage);
        return NULL;
    }

    manage->trie = InitNetwork(manage->trie, num_bits_in_subnet, &status);

    manage->num_bits_in_subnet = num_bits_in_subnet;

    memcpy(manage->network, network, BYTES_IN_IPv4);

    return manage;
}
/****************************************************************************/
void DHCPDestroy(dhcp_t *dhcp)
{
    assert(dhcp);

    TrieDestroy(dhcp->trie);
    dhcp->trie = NULL;

    free(dhcp);
}
/****************************************************************************/
status_t DHCPAllocateNewIP(dhcp_t *dhcp, const ip_t requested_ip, ip_t output)
{
    status_t status = SUCCESS;
    unsigned int out = 0;

    assert(dhcp);
    
    if( 0 == ConvertToInt(requested_ip) )
    {
        out = ConvertToInt(dhcp->network);
    }
    else
    {
        out = ConvertToInt(requested_ip);
    }

    if( FALSE == IsInNetwork(dhcp, ConvertToInt(requested_ip)))
    {
        ConvertToIP(0, output);
        return NOT_IN_NETWORK_ERROR;
    }

   
    TrieInsert(dhcp->trie,&out,TOTAL_BIT_NUM - dhcp->num_bits_in_subnet ,&status );


    if( SUCCESS != status )
    {
       out = 0;
    }

    ConvertToIP(out, output);

    return status;

}
/****************************************************************************/
status_t DHCPFreeIP(dhcp_t *dhcp, const ip_t ip_to_free)
{
    unsigned int requested_ip = 0;
    status_t status = SUCCESS;
    assert(dhcp);

    if( FALSE == IsInNetwork(dhcp, ConvertToInt(ip_to_free)))
    {
        return NOT_IN_NETWORK_ERROR;
    }
    requested_ip = ConvertToInt(ip_to_free);

    TrieFree(dhcp->trie, &requested_ip, TOTAL_BIT_NUM - dhcp->num_bits_in_subnet, &status);
    
    return status;
}
/****************************************************************************/
size_t DHCPCountFree(const dhcp_t *dhcp)
{
    size_t count = 0;
    int bits = 0;

    assert(dhcp);

    bits = TOTAL_BIT_NUM - dhcp->num_bits_in_subnet;

    count = 1 << bits ;

    count -= TrieCount(dhcp->trie,bits );

    return count;

}
/****************************************************************************
*                             TRIE IMPL
****************************************************************************/
static trie_node_t *TrieCreate(status_t *status)
{
    trie_node_t *root = CreateNode();
    if( NULL == root)
    {
        *status = ALLOC_ERROR;
        return NULL;
    }
    return root;
}
/****************************************************************************/
static trie_node_t *InitNetwork(trie_node_t *root,
                                unsigned int num_bits_in_subnet,
                                status_t *status)
{
    unsigned int bits = TOTAL_BIT_NUM - num_bits_in_subnet;
    unsigned int network_adr = 0;
    unsigned int server_adr = (1 << bits) -1;
    unsigned int broadcast_adr = server_adr - 1;

    if( NULL == TrieInsert(root,&network_adr,bits , status))
    {
        TrieDestroy(root);
        return NULL;
    }
    if( NULL == TrieInsert(root,&server_adr,bits, status))
    {
        TrieDestroy(root);
        return NULL;
    }
    if( NULL == TrieInsert(root,&broadcast_adr,bits ,status))
    {
        TrieDestroy(root);
        return NULL;
    }
    return root;
}
/****************************************************************************/
void TrieDestroy(trie_node_t* root)
{
    if( NULL == root )
    {
        return;
    }

    TrieDestroy(root->child[0]);
    TrieDestroy(root->child[1]);

    root->child[0] = NULL;
    root->child[1] = NULL;
    free(root);
}
/****************************************************************************/
static trie_node_t *TrieInsert(trie_node_t *root, 
                                unsigned int *output, 
                                unsigned int height,
                                status_t *status)
{
    int bit = 0;
    unsigned int mask = (unsigned int)1 << (height - 1);
    /*
    exit condition for height 0
    */
    if( 0 == height)
    {
        root->is_full = TRUE;
        return root;
    }

    bit = !!(*output & mask);   
    /*
    creating node if needed
    */
    if( NULL == root->child[bit] )
    {
        root->child[bit] = CreateNode();
        if( NULL == root->child[bit])
        {
            *status = ALLOC_ERROR;
            return root;
        }
    }
    /*
    if one of the bits on the route is taken 
    */
    if(root->child[bit]->is_full) 
    {
        if( 1 == bit ) /*one bit is taken*/
        {
            *status = IP_NOT_FOUND_ERROR;
            return root;
        }
        else /*zero bit is taken*/
        {
            *output |= ((unsigned int)1 << (height - 1));
            *output &= ((unsigned int)-1 << (height - 1));
            root = TrieInsert(root,output,height ,status );
        }
    }
    else/*non taken situation */
    {
        root->child[bit] = TrieInsert(root->child[bit],output,height - 1,status ); 
    }
    /*
    case we piped from one is ocupied
    */
    if( IP_NOT_FOUND_ERROR == *status )
    {
        /*going top meanwhile piping one is ocupied*/
        if(((*output >> (height - 1)) & 1) == 1)
        {
            return root;
        }
        *output += 1;

        /*get fixed root by allocating above*/
        if( NULL == root->child[bit] )
        {
            root = TrieInsert(root,output,height ,status );
        }
        *status = SUCCESS;
        root->child[bit] = TrieInsert(root->child[bit],output,height - 1,status ); 
    }
    UpdateIsFull(root);
    return root;                                            
}
/****************************************************************************/
static size_t TrieCount(const trie_node_t *root, unsigned int height)
{
    if(NULL == root)
    {
        return 0;
    }

    if( root->is_full )
    { 
        return((1)<< height);
    }

    return TrieCount(root->child[0], height - 1) + TrieCount(root->child[1], height - 1);
}
/****************************************************************************/
static trie_node_t *TrieFree(trie_node_t *root, unsigned int *requested_ip,
                                                            unsigned int height,
                                                             status_t *status)
{
    int bit = 0;
    unsigned int mask = (unsigned int)1 << (height - 1);


    bit = !!(*requested_ip & mask);   
                                
    if( 0 == height)
    {
        root->is_full = FALSE;
        return root;
    }

    if( NULL == root->child[bit] )
    {
        *status = IP_NOT_FOUND_ERROR;
        return root;
    }
    
    root->child[bit] = TrieFree(root->child[bit],requested_ip,height - 1,status);
    
    UpdateIsFull(root);

    return root;
}
/****************************************************************************
*                             UTIL IMPL
****************************************************************************/
static trie_node_t *CreateNode(void)
{
    trie_node_t *node = (trie_node_t*)malloc(sizeof(trie_node_t));
    if(NULL == node)return NULL;

    node->child[0] = NULL;
    node->child[1] = NULL;
    node->is_full = FALSE;

    return node;
}
/****************************************************************************/
static void UpdateIsFull(trie_node_t *root)
{
    if (root->child[0] && root->child[1])
    {
        root->is_full = (root->child[0]->is_full && 
                        root->child[1]->is_full);
    }
}
/****************************************************************************/
static unsigned int ConvertToInt(const ip_t ip)
{
    unsigned int res = 0;
    size_t i = 0;
    for (i = 0; i < BYTES_IN_IPv4 - 1; ++i)
    {
        res |= ((unsigned int)ip[i]);
        res = res << CHAR_BIT;
    }

    res |= ((unsigned int)ip[i]);

    return res;
}
/****************************************************************************/
static void ConvertToIP(unsigned int ip, ip_t out)
{
    int i = BYTES_IN_IPv4 - 1;
    unsigned int mask = 0xff;
    for (i = BYTES_IN_IPv4 - 1; i > 0; --i)
    {
        out[i] = (ip & mask);
        ip = ip >> CHAR_BIT;
    }
    out[i] = (ip & mask);
}
/****************************************************************************/
static int IsInNetwork(const dhcp_t *dhcp, unsigned int requested_ip)
{
    unsigned int res_network = 0;
    unsigned int res_requested = 0;
    int bits = TOTAL_BIT_NUM - dhcp->num_bits_in_subnet;
    unsigned int mask = (unsigned int)-1 <<  bits;

    res_network = ConvertToInt(dhcp->network) & mask;
    res_requested = requested_ip & mask;

    return (res_requested == res_network || res_requested == 0);
}





