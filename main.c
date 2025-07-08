#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BARANG 100

struct Barang {
    char nama_barang[100];
    int kode_barang;
    int harga;
    int stok_barang;
    int index;
};

void progAwal(struct Barang *b);
void daftarBarang(struct Barang *b, int kode);
void tambahBarang(struct Barang *barangArray, int *jumlahBarang);
int cariBarang(struct Barang *b, int kodeCari);
void hapusBarang(struct Barang *b, int indeksHapus);
void kasir(struct Barang *b);
void pembayaran(int total_bayar);
void kembalianUang(int kembalian);

int main(int argc, char *argv[]) {
    struct Barang b[MAX_BARANG];

    progAwal(b);
    return 0;
}

void progAwal(struct Barang *b) {
    int pilihan, kodeCari, indeksHapus;
    printf("Anggota : Ahmad Faiz Zaenuddin  2350081085 \n");
    printf("\n\t========== WELCOME TO TOKO TALI JAPIT ===========\n");
    printf("\t------- MENJUAL BERBAGAI TALI JEPIT SANDAL -------\n");
    printf("\t===============================================\n");
    printf("\n1. Menambah Barang\n");
    printf("2. Menghapus Barang\n");
    printf("3. Daftar Barang\n");
    printf("4. Kasir\n");

    printf("Pilihan : ");
    scanf("%d", &pilihan);
	
    switch (pilihan) {
        case 1:
            tambahBarang(b, &(b[0].index)); // Menggunakan alamat indeks sebagai parameter
            break;
        case 2:
        	if(b[0].index != 0){
        		printf("Masukkan kode barang yang ingin dihapus: ");
	            scanf("%d", &kodeCari);
	            indeksHapus = cariBarang(b, kodeCari);
	            if (indeksHapus != -1) {
	                hapusBarang(b, indeksHapus);
	                printf("===> Berhasil dihapus.\n", kodeCari);
	                daftarBarang(b, 1);
	            } else {
	                printf("===> Barang dengan kode %d tidak ditemukan.\n", kodeCari);
	                daftarBarang(b, 1);
	            }
	            break;
			}else{
				printf("===> Daftar barang kosong.\n\n\n");
				progAwal(b);
				break;
			}
        case 3:
            daftarBarang(b, 1);
            break;
        case 4:
            kasir(b);
            break;
        default:
            printf("===> Pilihan tidak tersedia, masukkan angka yang benar!\n\n");
            progAwal(b);
    }
}

void kasir(struct Barang *b) {
	if(b[0].index != 0){
		int i, jml_pembelian, kode_barang, indek_barang, total_harga = 0, total_bayar, bayar;
    int diskon = 0;
    int kodbar[MAX_BARANG];
    
    printf("\n\t========== WELCOME TO TOKO TALI JEPIT===========\n");
    printf("\t------- MENJUAL BERBAGAI TALI JEPIT SALDAL -------\n");
    printf("\t===============================================\n");
    
    // Inisialisasi semua elemen array kodbar menjadi 0 
    memset(kodbar, 0, sizeof(kodbar));

    int *jml_barang = (int *)malloc(MAX_BARANG * sizeof(int)); // Menyimpan jumlah barang yang dibeli

    daftarBarang(b, 0);

    printf("Jumlah pembelian : ");
    scanf("%d", &jml_pembelian);

	if(jml_pembelian != 909090){
		for (i = 0; i < jml_pembelian; i++) {
        printf("\nBarang %d\n", i + 1);
        printf("Kode barang : ");
        scanf("%d", &kode_barang);

        indek_barang = cariBarang(b, kode_barang);
		kodbar[i] = kode_barang;
		
        // Memastikan barang ditemukan dan stok mencukupi
        if (indek_barang != -1 && b[indek_barang].stok_barang > 0) {
            printf("Nama barang : %s\n", b[indek_barang].nama_barang);
            printf("Harga barang : Rp%d\n", b[indek_barang].harga);
            printf("Stok tersedia : %d\n", b[indek_barang].stok_barang);

            printf("Jumlah barang : ");
            scanf("%d", &jml_barang[i]); // Simpan jumlah barang yang dibeli
            // Memastikan jumlah barang yang diminta tidak melebihi stok yang tersedia
            if (jml_barang[i] <= b[indek_barang].stok_barang) {
                // Update total harga dengan harga barang * jumlah barang
                total_harga += b[indek_barang].harga * jml_barang[i];

                // Mengurangi stok pada struct barang sesuai jumlah barang yang dibeli
                b[indek_barang].stok_barang -= jml_barang[i];
            } else {
                printf("===> Maaf, stok tidak mencukupi.\n");
                i--; // Mengulangi pembelian untuk barang yang tidak mencukupi stok
            }
        }else {
            printf("===> Barang dengan kode %d tidak ditemukan atau stok habis.\n", kode_barang);
            i--; // Mengulangi pembelian untuk barang yang tidak ditemukan atau stok habis
        	}
    	}

	    printf("\n===================RINGKASAN PEMBELIAN=====================\n");
	    printf("Kode Barang\tNama Barang\tJumlah\tHarga\tTotal Harga\n");
	
	    for (i = 0; i < jml_pembelian; i++) {
	    	indek_barang = cariBarang(b, kodbar[i]); 
	    	printf("%d\t\t%s\t\t%d\tRp%d\tRp%d\n", b[indek_barang].kode_barang, b[indek_barang].nama_barang, jml_barang[i], 
			b[indek_barang].harga, b[indek_barang].harga*jml_barang[i]);
		}
	
	    /*
	    	Diskon
	    	pemberlian >500rb = 5%
	    	pembelian >250rb = 3%
	    	pembelian >100rb = 1%
		*/
	    if (total_harga > 500000) {
	        diskon = 5;
	    } else if (total_harga > 250000) {
	        diskon = 3;
	    } else if (total_harga > 100000) {
	        diskon = 1;
	    }
	
	    total_bayar = total_harga - (total_harga * diskon / 100);
	
	    printf("\n============ PEMBAYARAN ============\n");
	    printf("Total Harga : Rp%d\n", total_harga);
	    printf("Diskon      : Rp%d\n", total_harga * diskon / 100);
	    printf("Total Bayar : Rp%d\n", total_bayar);
	    
	    pembayaran(total_bayar);
	    
		printf("\n\t ===== TERIMA KASIH ATAS KUNJUNGAN ANDA =====");
	    printf("\n\t ---- SEMOGA ANDA PUAS DENGAN PRODUK KAMI ----");
	    printf("\n\t    ======== SELAMAT DATANG KEMBALI ========\n");
	    
	    kasir(b);
	}else{
		progAwal(b);
	}
	}else{
		printf("===> Daftar barang kosong, silahkan diisi terlebih dahulu\n\n");
		progAwal(b);	
	}
}

void pembayaran(int total_bayar){
	int bayar, kembalian;
	
	printf("Bayar 	: ");
	scanf("%d", &bayar);
	if(bayar < total_bayar){
		printf("===> Uangnya kurang");
		pembayaran(total_bayar);
	}else{
		kembalian = bayar - total_bayar;
		kembalianUang(kembalian);
	}
}

void kembalianUang(int kembalian) {
    int seratusRb, limapuluhRb, duapuluhRb, sepuluhRb, limaRb, duaRb, seribu, limaratus, seratus, kemAsli;
    
    kemAsli = kembalian;
    
    seratusRb = kembalian / 100000;
    kembalian %= 100000;
    
    limapuluhRb = kembalian / 50000;
    kembalian %= 50000;
    
    duapuluhRb = kembalian / 20000;
    kembalian %= 20000;
    
    sepuluhRb = kembalian / 10000;
    kembalian %= 10000;
    
    limaRb = kembalian / 5000;
    kembalian %= 5000;
    
    duaRb = kembalian / 2000;
    kembalian %= 2000;
    
    seribu = kembalian / 1000;
    kembalian %= 1000;
    
    limaratus = kembalian / 500;
    kembalian %= 500;
    
    seratus = kembalian / 100;
    
    printf("\n============= KEMBALIAN =============\n");
    printf("Total kembalian : %d\n", kemAsli);
    if (seratusRb > 0) printf("Seratus ribu : %d lembar\n", seratusRb);
    if (limapuluhRb > 0) printf("Limapuluh ribu : %d lembar\n", limapuluhRb);
    if (duapuluhRb > 0) printf("Duapuluh ribu : %d lembar\n", duapuluhRb);
    if (sepuluhRb > 0) printf("Sepuluh ribu : %d lembar\n", sepuluhRb);
    if (limaRb > 0) printf("Lima ribu : %d lembar\n", limaRb);
    if (duaRb > 0) printf("Dua ribu : %d lembar\n", duaRb);
    if (seribu > 0) printf("Seribu : %d lembar\n", seribu);
    if (limaratus > 0) printf("Lima ratus : %d lembar\n", limaratus);
    if (seratus > 0) printf("Seratus : %d lembar\n", seratus);
    printf("\n=======================================\n");
}

int cariBarang(struct Barang *b, int kodeCari) {
    int i;

    for (i = 0; i < b[0].index; i++) {
        if (b[i].kode_barang == kodeCari) {
            return i; // Mengembalikan indeks jika ditemukan
        }
    }
    return -1; // Mengembalikan -1 jika tidak ditemukan
}

void hapusBarang(struct Barang *b, int indeksHapus) {
		int i;
		memmove(&b[indeksHapus], &b[indeksHapus + 1], (b[0].index - indeksHapus - 1) * sizeof(struct Barang));
	
	    // Mengurangi jumlah barang yang ada di dalam array
	    (b[0].index)--;
	    
	    // Memperbarui indeks setiap barang setelah penghapusan
	    for (i = indeksHapus; i < b[0].index; i++) {
	        b[i].index = i;
	    }
}

void daftarBarang(struct Barang *b, int kode) {
    int i;

    printf("\n=================DAFTAR BARANG=================\n");
    printf("Kode Barang\tNama Barang\t\tStok\t\tHarga\n");
    for (i = 0; i < b[0].index; i++) {
        printf("%d\t\t%s\t\t%d\t\tRp%d\n", b[i].kode_barang, b[i].nama_barang, b[i].stok_barang, b[i].harga);
    }
    printf("===============================================\n\n\n");
    if (kode == 1){
    	progAwal(b);
	}else{
		
	}
}

void tambahBarang(struct Barang *barangArray, int *jumlahBarang) {
    int indek, i, harga, stok, jumlahBarangBaru;
    char namaBarang[100];

    printf("Masukkan jumlah barang yang akan ditambah : ");
    scanf("%d", &jumlahBarangBaru);

    for (i = 0; i < jumlahBarangBaru; i++) {
        printf("\nBarang %d\n", i + 1);
        printf("Nama Barang  : ");
        scanf("%s", namaBarang);
        printf("Harga Barang : Rp.");
        scanf("%d", &harga);
        printf("Jumlah Stok  : ");
        scanf("%d", &stok);

        if ((*jumlahBarang + jumlahBarangBaru) < MAX_BARANG) {
            // Mengisi data barang
            indek = *jumlahBarang; // Mengubah indek agar sesuai dengan jumlah barang
            strncpy(barangArray[indek].nama_barang, namaBarang, sizeof(barangArray[indek].nama_barang) - 1);
            barangArray[indek].nama_barang[sizeof(barangArray[indek].nama_barang) - 1] = '\0'; 
            barangArray[indek].kode_barang = 1000 + indek; 
            barangArray[indek].harga = harga;
            barangArray[indek].stok_barang = stok;
            barangArray[indek].index = indek;

            // Menambah jumlah barang yang ada di dalam array
            *jumlahBarang += 1;
        } else {
            printf("===> Daftar barang sudah penuh. Tidak bisa menambahkan barang lagi.\n");
            progAwal(barangArray);
        }
    }
    printf("===> Barang berhasil ditambahkan.\n");
    progAwal(barangArray);
}

