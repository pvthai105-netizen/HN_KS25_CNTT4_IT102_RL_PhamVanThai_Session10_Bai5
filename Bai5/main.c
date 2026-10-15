#include <stdio.h>
#include <string.h>

#define MAX_TICKETS 5

struct Ticket {
    int ticket_id;
    char event_name[50];
    double price;
    int is_vip;
};

/* Khai bao nguyen mau ham */
double tinh_gia_ve(double price, int is_vip);
int tim_ve(const struct Ticket list[], int total_tickets, int ticket_id);
void hien_thi_danh_sach(const struct Ticket list[], int total_tickets);
int them_ve(struct Ticket list[], int total_tickets, struct Ticket ve_moi);
int xoa_ve(struct Ticket list[], int total_tickets, int ticket_id);

int main(void) {
    struct Ticket list[MAX_TICKETS] = {
        {101, "Concert", 500000.0, 0},
        {102, "MusicShow", 500000.0, 1}
    };

    int total_tickets = 2;

    struct Ticket ve_moi;

    printf("=== DANH SACH VE BAN DAU ===\n");
    hien_thi_danh_sach(list, total_tickets);

    printf("\nGia thanh toan ve VIP: %.0f VND\n",
           tinh_gia_ve(500000.0, 1));

    /* Them ve moi */
    printf("\n=== THEM VE ===\n");

    ve_moi.ticket_id = 103;
    strcpy(ve_moi.event_name, "RockShow");
    ve_moi.price = 300000.0;
    ve_moi.is_vip = 0;
    total_tickets = them_ve(list, total_tickets, ve_moi);

    ve_moi.ticket_id = 104;
    strcpy(ve_moi.event_name, "DanceShow");
    ve_moi.price = 400000.0;
    ve_moi.is_vip = 1;
    total_tickets = them_ve(list, total_tickets, ve_moi);

    ve_moi.ticket_id = 105;
    strcpy(ve_moi.event_name, "JazzShow");
    ve_moi.price = 350000.0;
    ve_moi.is_vip = 0;
    total_tickets = them_ve(list, total_tickets, ve_moi);

    ve_moi.ticket_id = 106;
    strcpy(ve_moi.event_name, "PopShow");
    ve_moi.price = 450000.0;
    ve_moi.is_vip = 1;
    total_tickets = them_ve(list, total_tickets, ve_moi);

    printf("\nSo luong ve hien tai: %d\n", total_tickets);
    hien_thi_danh_sach(list, total_tickets);

    /* Xoa ma ve khong ton tai */
    printf("\n=== XOA VE KHONG TON TAI ===\n");
    total_tickets = xoa_ve(list, total_tickets, 999);

    /* Xoa ve hop le */
    printf("\n=== XOA VE 102 ===\n");
    total_tickets = xoa_ve(list, total_tickets, 102);

    printf("\n=== DANH SACH SAU KHI XOA ===\n");
    hien_thi_danh_sach(list, total_tickets);

    printf("\nTong so ve hien tai: %d\n", total_tickets);

    return 0;
}

/* Tinh gia ve, VIP phu thu 20% */
double tinh_gia_ve(double price, int is_vip) {
    if (is_vip == 1) {
        return price * 1.2;
    }

    return price;
}

/* Tim vi tri ve theo ma, khong tim thay thi tra ve -1 */
int tim_ve(const struct Ticket list[], int total_tickets, int ticket_id) {
    int i;

    for (i = 0; i < total_tickets; i++) {
        if (list[i].ticket_id == ticket_id) {
            return i;
        }
    }

    return -1;
}

/* Hien thi danh sach ve */
void hien_thi_danh_sach(const struct Ticket list[], int total_tickets) {
    int i;

    if (total_tickets == 0) {
        printf("Danh sach ve dang rong!\n");
        return;
    }

    printf("%-10s %-15s %-15s %-10s %-15s\n",
           "Ma ve", "Su kien", "Gia goc", "Loai ve", "Gia thanh toan");

    for (i = 0; i < total_tickets; i++) {
        printf("%-10d %-15s %-15.0f %-10s %-15.0f\n",
               list[i].ticket_id,
               list[i].event_name,
               list[i].price,
               list[i].is_vip == 1 ? "VIP" : "Thuong",
               tinh_gia_ve(list[i].price, list[i].is_vip));
    }
}

/* Them ve moi, tra ve so luong ve sau thao tac */
int them_ve(struct Ticket list[], int total_tickets, struct Ticket ve_moi) {
    if (total_tickets >= MAX_TICKETS) {
        printf("Danh sach ve da day!\n");
        return total_tickets;
    }

    if (tim_ve(list, total_tickets, ve_moi.ticket_id) != -1) {
        printf("Ma ve %d da ton tai!\n", ve_moi.ticket_id);
        return total_tickets;
    }

    list[total_tickets] = ve_moi;

    printf("Them ve %d thanh cong!\n", ve_moi.ticket_id);

    return total_tickets + 1;
}

/* Xoa ve bang cach don cac phan tu phia sau sang trai */
int xoa_ve(struct Ticket list[], int total_tickets, int ticket_id) {
    int index;
    int i;

    if (total_tickets == 0) {
        printf("Danh sach ve dang rong!\n");
        return total_tickets;
    }

    index = tim_ve(list, total_tickets, ticket_id);

    if (index == -1) {
        printf("Khong tim thay ma ve %d!\n", ticket_id);
        return total_tickets;
    }

    for (i = index; i < total_tickets - 1; i++) {
        list[i] = list[i + 1];
    }

    printf("Xoa ve %d thanh cong!\n", ticket_id);

    return total_tickets - 1;
}
