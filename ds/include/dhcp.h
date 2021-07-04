/****************************************************************************
* FILE: dhcp_test.c  Purpose: library for dhpc protocol
*
* DEVELOPER:   Daniel Zaken				TEAM: Green
*
* REVIEWER:    Kim Aharfi				STATUS: Approved
*
****************************************************************************/
#ifndef __ILRD_DHCP_H__
#define __ILRD_DHCP_H__

#include <stddef.h> /* size_t */

#define BYTES_IN_IPv4 (4)
typedef struct dhcp dhcp_t;
typedef unsigned char ip_t[BYTES_IN_IPv4];

typedef enum status
{
    SUCCESS = 0,
    IP_NOT_FOUND_ERROR = 1,
    ALLOC_ERROR = 2,
    NOT_IN_NETWORK_ERROR = 3
}status_t;

/*****************************************************************************/
 /*
  * Description: Creates an instance of a DHCP.
  * Return value: returns a a pointer to the created DHCP instance.
  * Time Complexity:
 */
dhcp_t *DHCPCreate(const ip_t network, unsigned int num_bits_in_subnet);

/*****************************************************************************/
 /*
  * Description: Destroys the DHCP instance pointed to by dhcp.
  * Return value: None
  * Time Complexity:
 */
void DHCPDestroy(dhcp_t *dhcp);

/*****************************************************************************/
 /*
  * Description: Allocates a new IP address, if the requested IP address is 
  *             free, it is allocated, otherwise an IP address that is the 
  *             closest and greater than the requested IP address is allocated.
  *             If there is no IP address preference, an IP of 0.0.0.0 should
  *             be passed in as the requested address.
  * Return value: 0 upon success, non-zero value that will indicate the failure 
  *               by the status_t value otherwise.
  * Time Complexity: O(LOG(N))
 */
status_t DHCPAllocateNewIP(dhcp_t *dhcp, const ip_t requested_ip, ip_t output);

/*****************************************************************************/
 /*
  * Description: Frees ip_to_free.
  * Return value: 0 upon success, non-zero value that will indicate the failure 
  *               by the status_t value otherwise.
  * Time Complexity: O(LOG(N))
 */
status_t DHCPFreeIP(dhcp_t *dhcp, const ip_t ip_to_free);

/*****************************************************************************/
 /*
  * Description: Counts the number of free IP addresses.
  * Return value: the number of free IP addresses.
  * Time Complexity: O(N)
 */
size_t DHCPCountFree(const dhcp_t *dhcp);
/*****************************************************************************/



#endif