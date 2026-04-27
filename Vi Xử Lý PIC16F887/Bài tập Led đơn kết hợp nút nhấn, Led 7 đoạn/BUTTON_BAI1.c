#include <16F887.h>
#fuses INTRC_IO, NOWDT, PUT, NOPROTECT, NOLVP
#use delay(clock=8M)
#define NUT_NHAN PIN_E0
unsigned int8 che_do = 1;
int1 co_trang_thai = 0;
void xuat_32led(unsigned int32 du_lieu) {
    output_a((unsigned int8)(du_lieu));
    output_b((unsigned int8)(du_lieu >> 8));
    output_c((unsigned int8)(du_lieu >> 16));
    output_d((unsigned int8)(du_lieu >> 24));
}
void kiem_tra_nut_nhan_tre(unsigned int16 thoi_gian) {
    unsigned int16 i;
    for(i=0; i<thoi_gian; i++)
    {
        if (!input(NUT_NHAN)) 
        {
            delay_ms(20);
            if (!input(NUT_NHAN)) 
            {
                che_do++;
                if (che_do > 7) che_do = 1;
                co_trang_thai = 1;
                while(!input(NUT_NHAN)); 
                return;
            }
        }
        delay_ms(1);
    }
}
void chop_tat() {
    unsigned int8 i;
    for(i=0; i<5; i++)
    {
        xuat_32led(0xFFFFFFFF);
        kiem_tra_nut_nhan_tre(500); if(co_trang_thai) return;
        xuat_32led(0x00000000);
        kiem_tra_nut_nhan_tre(500); if(co_trang_thai) return;
    }
}
void sang_tat_phai_sang_trai() {
    unsigned int8 k, i;
    unsigned int32 gia_tri;
    for(k=0; k<2; k++)
    {
        gia_tri = 0;
        for(i=0; i<32; i++)
        {
            gia_tri = (gia_tri << 1) + 0x01; 
            xuat_32led(gia_tri);
            kiem_tra_nut_nhan_tre(100); if(co_trang_thai) return;
        }
        for(i=0; i<32; i++)
        {
            gia_tri = (gia_tri << 1);
            xuat_32led(gia_tri);
            kiem_tra_nut_nhan_tre(100); if(co_trang_thai) return;
        }
    }
}
void sang_tat_trai_sang_phai() {
    unsigned int8 k, i;
    unsigned int32 gia_tri;
    for(k=0; k<2; k++)
    {
        gia_tri = 0;
        for(i=0; i<32; i++)
        {
            gia_tri = (gia_tri >> 1) | 0x80000000; 
            xuat_32led(gia_tri);
            kiem_tra_nut_nhan_tre(100); if(co_trang_thai) return;
        }
        for(i=0; i<32; i++)
        {
            gia_tri = (gia_tri >> 1);
            xuat_32led(gia_tri);
            kiem_tra_nut_nhan_tre(100); if(co_trang_thai) return;
        }
    }
}
void sang_tat_ngoai_vao() {
    unsigned int8 k, i;
    unsigned int32 trai, phai;
    for(k=0; k<2; k++)
    {
        trai = 0; phai = 0;
        for(i=0; i<16; i++)
        {
            trai = (trai >> 1) | 0x80000000;
            phai = (phai << 1) + 0x01;
            xuat_32led(trai | phai);
            kiem_tra_nut_nhan_tre(100); if(co_trang_thai) return;
        }
        for(i=0; i<16; i++)
        {
            trai = (trai >> 1) & 0xFFFF0000;   
            phai = (phai << 1) & 0x0000FFFF; 
            xuat_32led(trai | phai);
            kiem_tra_nut_nhan_tre(100); if(co_trang_thai) return;
        }
    }
}
void sang_tat_trong_ra() {
    unsigned int8 k, i;
    unsigned int32 trai, phai;
    for(k=0; k<2; k++)
    {
        trai = 0; phai = 0;
        for(i=0; i<16; i++)
        {
            trai = (trai << 1) | 0x00010000;
            phai = (phai >> 1) | 0x00008000;
            xuat_32led(trai | phai);
            kiem_tra_nut_nhan_tre(100); if(co_trang_thai) return;
        }
        for(i=0; i<16; i++)
        {
            trai = (trai << 1) & 0xFFFF0000;
            phai = (phai >> 1) & 0x0000FFFF;
            xuat_32led(trai | phai);
            kiem_tra_nut_nhan_tre(100); if(co_trang_thai) return;
        }
    }
}
void main() {
    set_tris_a(0x00);
    set_tris_b(0x00);
    set_tris_c(0x00);
    set_tris_d(0x00);
    set_tris_e(0xFF);
    xuat_32led(0x00000000);
    while(1) {
        co_trang_thai = 0;
        switch(che_do) {
            case 1: chop_tat(); break;
            case 2: sang_tat_phai_sang_trai(); break;
            case 3: chop_tat(); break;
            case 4: sang_tat_trai_sang_phai(); break;
            case 5: sang_tat_ngoai_vao(); break;
            case 6: chop_tat(); break;
            case 7: sang_tat_trong_ra(); break;
        }
    }
}
