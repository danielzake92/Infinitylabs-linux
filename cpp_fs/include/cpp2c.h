
/****************************************************************************
* FILE: cpp2c.h 		            PURPOSE: Coding cpp in c
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: Elizabeta				STATUS: IMPL DONE
*
*
****************************************************************************/
#ifndef __ILRD_RD100_CPP2C_HPP__
#define __ILRD_RD100_CPP2C_HPP__

/********************structs***************************/

/********************Public Transport******************/

typedef struct pt pt_t;
typedef struct pt_vtbl pt_vtbl_t;

struct pt_vtbl
{
   void (*dtor)(pt_t *const this);
   void (*display)(pt_t *const this);
};

struct pt
{
    void *vptr;
    int m_license_plate;
};

void CtorPT(pt_t *const this);
void DtorPT(pt_t *const this);
void CctorPT(pt_t *const this, const pt_t * const other); 
void DisplayPT(pt_t *const this);

/********************Minibus******************/

typedef struct mb mb_t;
typedef struct mb_vtbl mb_vtbl_t;

struct mb_vtbl
{
   void (*dtor)(mb_t *const this);
   void (*display)(mb_t *const this);
   void (*wash)(mb_t *const this, int minutes);
};

struct mb
{
    pt_t pt;
    int m_num_seats;
};

void CtorMB(mb_t *const this);
void DtorMB(mb_t *const this);
void CctorMB(mb_t *const this, const mb_t * const other);
void DisplayMB(mb_t *const this);
void WashMB(mb_t *const this, int minutes);

/********************Taxi******************/

typedef struct tx tx_t;
typedef struct tx_vtbl tx_vtbl_t;

struct tx_vtbl
{
   void (*dtor)(tx_t *const this);
   void (*display)(tx_t *const this);
};

struct tx
{
    pt_t pt;
};

void CtorTX(tx_t *const this);
void DtorTX(tx_t *const this);
void CctorTX(tx_t *const this, const tx_t * const other);
void DisplayTX(tx_t *const this);

/********************Special Taxi******************/

typedef struct stx stx_t;
typedef struct stx_vtbl stx_vtbl_t;

struct stx_vtbl
{
   void (*dtor)(stx_t *const this);
   void (*display)(stx_t *const this);
};

struct stx
{
    tx_t tx;
};

void CtorSTX(stx_t *const this);
void DtorSTX(stx_t *const this);
void CctorSTX(stx_t *const this, const stx_t * const other);
void DisplaySTX(stx_t *const this);

/*********************Other API functions********************/

void print_count();
int GetIdPT(pt_t *const this);

void print_infoRPT(pt_t *a);
void print_infoV(void);
void print_infoRMB(mb_t *m);
pt_t print_infoI(int i);
void taxi_displayTX(tx_t s);

void PrintCountPT();

#define IMax(a, b) ((a) > (b)) ? (a) : (b)

/********************************************************/
#endif //__ILRD_RD100_CPP2C_HPP__
