
/****************************************************************************
* FILE: cpp2c.c 		            PURPOSE: Coding cpp in c
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: Elizabeta				STATUS: Aproved
*
*
****************************************************************************/

#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include "cpp2c.h" //implemented lib for oop in c
/*****************************************************************************/
static const pt_vtbl_t pt_vtbl = {DtorPT, DisplayPT};
static const mb_vtbl_t mb_vtbl = {DtorMB, DisplayMB, WashMB};
static const tx_vtbl_t tx_vtbl = {DtorTX, DisplayTX};
static const stx_vtbl_t stx_vtbl = {DtorSTX, DisplaySTX};

static int s_count = 0; 


/*****************************************************************************/
/*****************************************************************************/
void CtorPT(pt_t *const this)
{
    this->vptr = (pt_vtbl_t*)(&pt_vtbl);
    this->m_license_plate = ++s_count;
    printf("PublicTransport::Ctor()%d\n",s_count);
}
/*****************************************************************************/
void CtorMB(mb_t *const this)
{
    CtorPT(&(this->pt));

    (this->pt).vptr = (mb_vtbl_t*)(&mb_vtbl);
    this->m_num_seats = 20;

    printf("Minibus::Ctor()\n");
}
/*****************************************************************************/
void CtorTX(tx_t *const this)
{
    CtorPT(&(this->pt));

    (this->pt).vptr = (tx_vtbl_t*)(&tx_vtbl);/* change to tx_vtbl */

    printf("Taxi::Ctor()\n");
}
/*****************************************************************************/
void CtorSTX(stx_t *const this)
{
    CtorTX(&(this->tx));

    ((this->tx).pt).vptr = (stx_vtbl_t*)(&stx_vtbl);/* change to stx_vtbl */

    printf("SpecialTaxi::Ctor()\n");
}
/*****************************************************************************/
void DtorPT(pt_t *const this)
{
    this->vptr = (pt_vtbl_t*)(&pt_vtbl);
    --s_count;
    printf("PublicTransport::Dtor()%d\n",this->m_license_plate);
}
/*****************************************************************************/
void DtorMB(mb_t *const this)
{
    (this->pt).vptr = (mb_vtbl_t*)(&mb_vtbl);
    printf("Minibus::Dtor()\n");
    DtorPT(&this->pt);
}
/*****************************************************************************/
void DtorTX(tx_t *const this)
{
    (this->pt).vptr = (tx_vtbl_t*)(&tx_vtbl);
    printf("Taxi::Dtor()\n");
    DtorPT(&this->pt);
}
/*****************************************************************************/
void DtorSTX(stx_t *const this)
{
    ((this->tx).pt).vptr = (stx_vtbl_t*)(&stx_vtbl);
    printf("SpecialTaxi::Dtor()\n");
    DtorTX(&this->tx);
}
/*****************************************************************************/
void CctorPT(pt_t *const this, const pt_t * const other)
{
    (void)other;
    this->vptr = (pt_vtbl_t*)(&pt_vtbl);
    this->m_license_plate = ++s_count;
    printf("PublicTransport::CCtor() %d\n",this->m_license_plate);
}
/*****************************************************************************/
void CctorMB(mb_t *const this, const mb_t * const other)
{
    CctorPT(&(this->pt), &(other->pt));
    (this->pt).vptr = (mb_vtbl_t*)(&mb_vtbl);/* change to mb_vtbl */
    this->m_num_seats = other->m_num_seats;
    printf("Minibus::CCtor()\n");
}
/*****************************************************************************/
void CctorTX(tx_t *const this, const tx_t * const other)
{
    CctorPT(&(this->pt), &(other->pt));
    (this->pt).vptr = (tx_vtbl_t*)(&tx_vtbl);/* change to tx_vtbl */
    printf("Taxi::CCtor()\n");
}
/*****************************************************************************/
void CctorSTX(stx_t *const this, const stx_t * const other)
{
    CctorTX(&(this->tx),&(other->tx));
    ((this->tx).pt).vptr = (stx_vtbl_t*)(&stx_vtbl);/* change to stx_vtbl */
    printf("SpecialTaxi::CCtor()\n");
}
/*****************************************************************************/
void DisplayPT(pt_t *const this)
{
    printf("PublicTransport::display(): %d\n",this->m_license_plate);
}
/*****************************************************************************/
void PrintCountPT()
{
    printf("s_count: %d\n",s_count);
}
/*****************************************************************************/
void DisplayMB(mb_t *const this)
{
    printf("Minibus::display() ID:%d",GetIdPT(&(this->pt)));
    printf(" num seats:%d\n",this->m_num_seats);
}
/*****************************************************************************/
void DisplayTX(tx_t *const this)
{
    printf("Taxi::display() ID:%d\n",GetIdPT(&(this->pt)));
}
/*****************************************************************************/
void DisplaySTX(stx_t *const this)
{
    printf("SpecialTaxi::display() ID:%d\n",GetIdPT(&(this->tx.pt)));
}
/*****************************************************************************/
void WashMB(mb_t *const this, int minutes)
{
    (void)this;
    printf("Minibus::wash(%d) ID:%d\n",minutes, GetIdPT(&(this->pt)));
}
/*****************************************************************************/
int GetIdPT(pt_t *const this)
{
    return this->m_license_plate;    
}
/*****************************************************************************/
void print_infoRPT(pt_t *a)
{
    (((pt_vtbl_t*)(a->vptr))->display)(a);
}
/*****************************************************************************/
void print_infoV(void)
{
    PrintCountPT();
}
/*****************************************************************************/
void print_infoRMB(mb_t *m)
{
    ((mb_vtbl_t*)((m->pt).vptr))->wash(m, 3);
}
/*****************************************************************************/
pt_t print_infoI(int i)
{
    (void)i;
    mb_t ret;
    CtorMB(&ret);
    printf("print_info(int i)\n");
    DisplayMB(&ret);

    pt_t temp_copy;
    CctorPT(&temp_copy , &(ret.pt));

    DtorMB(&ret);
    return temp_copy; 
}
/*****************************************************************************/
void taxi_displayTX(tx_t s)
{
    DisplayTX(&s);
}
/*****************************************************************************/
