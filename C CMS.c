//Judul : C CMS (Content Management System blog menggunakan bahasa C)
//Dibuat oleh Andre Pamungkas (A11.2015.09215) dan Fuad Abdulloh S.z (A11.2015.09218)
//Pada 24 Desember 2015
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

//Kamus
//kamus operasi file
FILE *loginfile[3],*tampil,*tambah,*daftarfile;
//tipe bentukan untuk login dan register
struct data_user
{
    char username[26],password[26];
};
struct data_user login,daftar;
//tipe bentukan untuk penampung data
struct data_tampung
{
    char konten,isifile,post,user[100],judulpost[100],lokasifolder[50],tengah[100];
    int jmldata;
};
struct data_tampung tampung;
//tipe bentukan penyimpan/penampung alamat file
struct data_url
{
    char hapuspost[100],post[100],user[100],database[100];
};
struct data_url url;
char datalogin[60][100],menu[20],menu2[20],menu3[20],isijudul[100],ulang,ulang2,ulang3;
int i,pilihpost,statushapus;
//kamus operasi folder
DIR *folder;
struct dirent *dir;

//prototype
void daftaruser();
void ubahdatalogin();
int hitungfile(char lokasifolder[]);
void tampilkanfile(char lokasifolder[]);
void tampilkanpost();
void tambahkanpost();
void hapuspost();

//Deskripasi
int main()
{
    do
    {
        system("color 3f");
        system("cls");
        system("title Home - DinusBlog");
        printf("--------------------------------------------------------------------------------\n");
        printf("                                   DINUSBLOG\n");
        printf("                        - Simplicity Blog with C CMS -\n");
        printf("\n--------------------------------------------------------------------------------\n\n");
        printf("\n                          Selamat Datang Di DinusBlog\n");
        printf("\n                                     Menu:\n");
        printf("                              +----------------+\n");
        printf("                              | login | daftar |\n");
        printf("                              +----------------+\n\n");
        printf("\n\n-------------------------------------------------------------------------------\n");
        printf(" | URL | http://dinusblog.id/");scanf("%s",&menu);
        //jika user memilih menu login
        if(strcmp(menu,"login")==0)
        {
            //membersihkan layar sebelumnya
            system("cls");
            system("title Login - DinusBlog");
            //pengguna memasukkan username dan password
            printf("--------------------------------------------------------------------------------\n");
            printf("                                   DINUSBLOG\n");
            printf("                        - Simplicity Blog with C CMS -\n");
            printf("\n--------------------------------------------------------------------------------\n\n");
            printf("\n                        Masukkan username dan password!\n");
            printf("\n Username : ");scanf("%s",&login.username);
            printf(" Password : ");scanf("%s",&login.password);
            //menampung isi username ke variabel tampung.user
            strcpy(tampung.user,login.username);
            //menggabungkan isi password ke username
            strcat(login.username,login.password);
            //menghitung jumlah user yang terdaftar
            //untuk digunakan sebagai looping
            tampung.jmldata=hitungfile("login");
            //looping untuk mencari data yang sesuai username dan password
            i=0;
            while(i<tampung.jmldata)
            {
                //menyimpan lokasi folder ke
                sprintf(url.user,"db/login/user%d.txt",i);
                //membuka file sesuai lokasi file diatas
                loginfile[i]=fopen(url.user,"r");
                //memeriksa apakah file user yang akan dibuka ada/tidak
                //jika tidak ada akan muncul pesan kesalahan
                if(loginfile[i]==NULL)
                {
                    printf("Login gagal!");
                }
                //memeriksa jika file tidak kosong, maka isinya ditampung pada datalogin
                if(fgets(datalogin[i],100,loginfile[i])!=NULL)
                {
                    //mencari file user mana yang sesuai dengan username dan password yang dimasukkan diatass
                    if(strcmp(datalogin[i],login.username)==0)
                    {
                        //lakukan perintah dibawah ini jika benar
                        do
                        {
                            //membersihkan layar sebelumnya
                            system("cls");
                            system("title Dashboard - DinusBlog");
                            //menyapa dengan sebutan username
                            printf("--------------------------------------------------------------------------------\n");
                            printf("                                   DINUSBLOG\n");
                            printf("                        - Simplicity Blog with C CMS -\n");
                            printf("\n--------------------------------------------------------------------------------\n\n");
                            sprintf(tampung.tengah,"Halo %s!",tampung.user);
                            printf("\n%*s\n", 40+strlen(tampung.tengah)/2, tampung.tengah, 40-strlen(tampung.tengah)/2, "");
                            printf("\n                                     Menu:\n");
                            printf("                           +----------------------+\n");
                            printf("                           | post | ubahdatalogin |\n");
                            printf("                           +----------------------+\n\n");
                            printf("\n\n-------------------------------------------------------------------------------\n");
                            printf(" | URL | http://dinusblog.id/%s/dashboard/",tampung.user);scanf("%s",&menu2);
                            //jika pengguna mengetikkan "post"
                            if(strcmp(menu2,"post")==0)
                            {
                                do
                                {
                                    //membersihkan layar sebelumnya
                                    system("cls");
                                    system("title Dashboard / Post - DinusBlog");
                                    printf("--------------------------------------------------------------------------------\n");
                                    printf("                                   DINUSBLOG\n");
                                    printf("                        - Simplicity Blog with C CMS -\n");
                                    printf("\n--------------------------------------------------------------------------------\n\n");
                                    printf("\n                                     Menu:\n");
                                    printf("                          +-------------------------+\n");
                                    printf("                          | tampil | tambah | hapus |\n");
                                    printf("                          +-------------------------+\n\n");
                                    printf(" Daftar postingan anda :\n");
                                    printf(" +----------------------------------------------------- \n");
                                    //dibawah ini akan menampilkan file postingan sesuai user yang login
                                    //menyimpan alamat data post pada url.post
                                    sprintf(url.post,"db/post/%s",tampung.user);
                                    //membuka folder sesuai alamat post user
                                    folder = opendir(url.post);
                                    if (folder)
                                    {
                                        //looping mulai -1
                                        i=-1;
                                        //memeriksa apakah folder kosong atau tidak
                                        while ((dir = readdir(folder)) != NULL)
                                        {
                                            //menghilangkan nomor -1 dan 0 yang tidak berisi data postingan
                                            if(i<1)
                                            {
                                                printf("");
                                            }
                                            else
                                            {
                                                //menampilkan judul file(postingan)
                                                printf(" | %s\n",dir->d_name);
                                                printf(" +----------------------------------------------------- \n");
                                            }
                                            i=i+1;
                                        }
                                        //menutup folder yang tekah dibaca
                                        closedir(folder);
                                    }
                                    //input menu pada post
                                    printf("\n\n\n-------------------------------------------------------------------------------\n");
                                    printf(" | URL | http://dinusblog.id/%s/dashboard/post/",tampung.user);scanf("%s",&menu3);
                                    //menu tampil postingan
                                    if(strcmp(menu3,"tampil")==0)
                                    {
                                        //menampilkan prosedur untuk menampilkan postingan
                                        tampilkanpost();
                                    }
                                    //menu tambah postingan
                                    else if(strcmp(menu3,"tambah")==0)
                                    {
                                        //menampilkan prosedur untuk menambahkan postingan
                                        tambahkanpost();
                                    }
                                    //menu hapus postingan
                                    else if(strcmp(menu3,"hapus")==0)
                                    {
                                        //menampilkan prosedur untuk menghapus file
                                        hapuspost();
                                    }
                                    //jika menu yang dipilih tidak sesuai
                                    else
                                    {

                                        //membersihkan layar sebelumnya
                                        system("cls");
                                        system("title 404 - DinusBlog");
                                        printf("--------------------------------------------------------------------------------\n");
                                        printf("                                   DINUSBLOG\n");
                                        printf("                        - Simplicity Blog with C CMS -\n");
                                        printf("\n--------------------------------------------------------------------------------\n\n");
                                        //menampilkan pesan kesalahan
                                        printf("\n                                404 - DinusBlog\n");
                                        printf("                            Halaman Tidak Ditemukan\n");
                                    }
                                    printf("\n\n\n                           Kembali ke post (Y/N) ? ");
                                    fflush(stdin);
                                    //inputan untuk mengulang ke post
                                    scanf("%c",&ulang3);
                                }
                                while(ulang3=='y' || ulang3=='Y');
                            }
                            else if(strcmp(menu2,"ubahdatalogin")==0)
                            {
                                ubahdatalogin();
                            }
                            //jika pengguna salah memasukkan katakunci menu
                            else
                            {
                                //membersihkan layar sebelumnya
                                system("cls");
                                system("title 404 - DinusBlog");
                                printf("--------------------------------------------------------------------------------\n");
                                printf("                                   DINUSBLOG\n");
                                printf("                        - Simplicity Blog with C CMS -\n");
                                printf("\n--------------------------------------------------------------------------------\n\n");
                                //menampilkan pesan kesalahan
                                printf("\n                                404 - DinusBlog\n");
                                printf("                            Halaman Tidak Ditemukan\n");
                            }
                            printf("\n\n\n                         Kembali ke dashboard (Y/N) ? ");
                            fflush(stdin);
                            //inputan untuk mengulang ke dashboard
                            scanf("%c",&ulang2);
                        }
                        while(ulang2=='y' || ulang2=='Y');
                    }
                    //jika password salah akan muncul kesalahan
                    else
                    {
                        //memnersihkan layar sebelumnya
                        system("cls");
                        printf("--------------------------------------------------------------------------------\n");
                        printf("                                   DINUSBLOG\n");
                        printf("                        - Simplicity Blog with C CMS -\n");
                        printf("\n--------------------------------------------------------------------------------\n\n");
                        //menampilkan kesalahan username/password
                        printf("\n                           Username/Password salah!\n");
                    }
                }
                i=i+1;
            }
        }
        //jika user memilih menu daftar
        else if(strcmp(menu,"daftar")==0)
        {
            //menampilkan prosedur daftar user
            daftaruser();
        }
        //jika user salah memasukkan kata kunci menu
        else
        {
            //membersihkan layar sebelumnya
            system("cls");
            system("title 404 - DinusBlog");
            printf("--------------------------------------------------------------------------------\n");
            printf("                                   DINUSBLOG\n");
            printf("                        - Simplicity Blog with C CMS -\n");
            printf("\n--------------------------------------------------------------------------------\n\n");
            //menampilkan pesan kesalahan
            printf("\n                                404 - DinusBlog\n");
            printf("                            Halaman Tidak Ditemukan\n");
        }
        printf("\n\n\n                           Kembali ke home (Y/N) ? ");
        fflush(stdin);
        //inputan untuk kembali ke home
        scanf("%c",&ulang);
    }
    while(ulang=='y' || ulang=='Y');
}
//prosedur untuk fitur daftar
void daftaruser()
{
    //membersihkan layar sebelumnya
    system("cls");
    system("title Daftar - DinusBlog");
    printf("--------------------------------------------------------------------------------\n");
    printf("                                   DINUSBLOG\n");
    printf("                        - Simplicity Blog with C CMS -\n");
    printf("\n--------------------------------------------------------------------------------\n\n");
    printf("\n          Masukkan username dan password yang aman dan mudah diingat!\n\n");
    //inputan username dan password
    printf(" Username : ");scanf("%s",&daftar.username);
    printf(" Password : ");scanf("%s",&daftar.password);

    strcpy(tampung.user,daftar.username);
    //menggabungkan username dan password ke variabel username
    //untuk dimasukkan ke dalam database
    strcat(daftar.username,daftar.password);
    //mengitung jumlah database user
    //buatfile dengan nama user[id].txt
    //id akan terus berlanjut jika ada user yang mendaftar
    sprintf(tampung.lokasifolder,"db/login/user%d.txt",hitungfile("login"));
    //memeriksa file bisa dibuat atau tidak
    if((daftarfile=fopen(tampung.lokasifolder,"w")) == NULL)
    {
        //menampilkan pesan kesalahan
        puts("Data pendaftar tidak dapat dibuat!\n");
    }
    //menuliskan isi username dan password kedalam file database
    fprintf(daftarfile,"%s",daftar.username);
    //menampung alamat postingan untuk dibuat folder sesuai username yang dibuat
    sprintf(tampung.lokasifolder,"db/post/%s",tampung.user);
    //membuat folser baru
    mkdir(tampung.lokasifolder);
    //pesan jika pendaftaran berhasil
    printf("\n                              Pendaftaran sukses!");
    //menutup file database pendaftaran yang dibuat
    fclose(daftarfile);
}
//prosedur fitur mengubah data login
void ubahdatalogin()
{
    //membersihkan layar sebelumnya
    system("cls");
    system("title Dashboard / Ubah data login - DinusBlog");
    printf("--------------------------------------------------------------------------------\n");
    printf("                                   DINUSBLOG\n");
    printf("                        - Simplicity Blog with C CMS -\n");
    printf("\n--------------------------------------------------------------------------------\n\n");
    printf("\n            Ubah username dan password yang aman dan mudah diingat!\n\n");
    //inputan username dan password
    printf(" Username : ");scanf("%s",&daftar.username);
    printf(" Password : ");scanf("%s",&daftar.password);
    strcpy(tampung.user,daftar.username);
    //menggabungkan username dan password ke variabel username
    //untuk dimasukkan ke dalam database
    strcat(daftar.username,daftar.password);
    //memeriksa file bisa dibuat atau tidak
    if((daftarfile=fopen(url.user,"w")) == NULL)
    {
        //menampilkan pesan kesalahan
        puts("Perubahan data login gagal!\n");
    }
    //menuliskan isi username dan password kedalam file database
    fprintf(daftarfile,"%s",daftar.username);
    //menampung alamat postingan untuk dibuat folder sesuai username yang dibuat
    sprintf(tampung.lokasifolder,"db/post/%s",tampung.user);
    //membuat folser baru
    mkdir(tampung.lokasifolder);
    //pesan jika pendaftaran berhasil
    printf("\n                         Perubahan data login sukses!");
    //menutup file database pendaftaran yang dibuat
    fclose(daftarfile);
}
//prosedur fitur menghitung jumlah file pada folder
int hitungfile(char lokasifolder[])
{
    int jumlah;
    //menyimpan alamat database untuk dibuka foldernya
    sprintf(url.database,"db/%s",lokasifolder);
    //membuka alamat foldernya
    folder = opendir(url.database);
    if (folder)
    {
        i=-1;
        while ((dir = readdir(folder)) != NULL)
        {
            //melakukan penghitungan
            jumlah=i;
            i=i+1;
        }
        //menutup folder yang telah dibuka
        closedir(folder);
    }
    return (jumlah);
}
//prosedur fitur menampilkan list postingan
void tampilkanfile(char lokasifolder[])
{
    //menyimpan alamat database untuk ditampilkan file pada alamat yang dituju
    sprintf(url.database,"db/%s",lokasifolder);
    //membuka alamat folder yang telah disimpan
    folder = opendir(url.database);
    if (folder)
    {
        //looping mulai -1
        i=-1;
        //membuka folder dan memastikan folder tidak kosong
        while ((dir = readdir(folder)) != NULL)
        {
            //menghilangkan no -1 dan 0 karena nama file dibaca pada baris ke-3
            //maka baris ke-3 diatur agar menjadi nomor 1
            if(i<1)
            {
                printf("");
            }
            else
            {
                //menampilkan list posting
                printf(" | %d. | %s\n",i,dir->d_name);
                printf(" +----------------------------------------------------- \n");
            }
            i=i+1;
        }
        //menutup folder yang telah dibuka
        closedir(folder);
    }
}
//prosedur fitur menampilkan postingan
void tampilkanpost()
{
    //membersihkan layar sebelumnya
    system("cls");
    system("title Dashboard / Post / Tampil - DinusBlog");
    printf("--------------------------------------------------------------------------------\n");
    printf("                                   DINUSBLOG\n");
    printf("                        - Simplicity Blog with C CMS -\n");
    printf("\n--------------------------------------------------------------------------------\n\n");
    printf("\n Daftar postingan anda :\n");
    printf(" +----------------------------------------------------- \n");
    //menampung alamat folder untuk menampilkan list posting
    sprintf(tampung.lokasifolder,"post/%s",tampung.user);
    //menampilkan list posting
    tampilkanfile(tampung.lokasifolder);
    printf("\n Masukkan nomor postingan yang ingin dibuka : ");
    //inputan untuk memilih nomor posting
    scanf("%d",&pilihpost);
    //menampung alamat posting pada database
    sprintf(url.post,"db/post/%s",tampung.user);
    //membuka alamat yang telah ditampung
    folder = opendir(url.post);
    if (folder)
    {
        //looping dimulai dari -1
        i=-1;
        //membaca isi folder dan memastikan folder yang dibaca ada
        while ((dir = readdir(folder)) != NULL)
        {
            //melakukan pemilihan posting sesuai nomor urut
            if(pilihpost==i)
            {
                //menampung alamat post untuk sesi membuka posting
                sprintf(url.post,"db/post/%s/%s",tampung.user,dir->d_name);
                //menampung judul posting
                strcpy(tampung.judulpost,dir->d_name);
            }
            i=i+1;
        }
        //menutup folder yang telah dibaca
        closedir(folder);
    }
    //membersihkan layar sebelumnya
    system("cls");
    system("title Dashboard / Tampilkan Post - DinusBlog");
    printf("--------------------------------------------------------------------------------\n");
    printf("                                   DINUSBLOG\n");
    printf("                        - Simplicity Blog with C CMS -\n");
    printf("\n--------------------------------------------------------------------------------\n\n");
    //menampilkan judul yang telah ditampung
    sprintf(tampung.tengah,"%s!",tampung.judulpost);
    printf("\n%*s\n\n", 40+strlen(tampung.tengah)/2, strupr(tampung.tengah), 40-strlen(tampung.tengah)/2, "");
    //membuka alamat postingan
    tampil=fopen(url.post,"r");
    //membaca tiap karakter sampai batas akhir file
    while((tampung.post=getc(tampil))!=EOF)
    {
        //menampilkan tiap karakter
        putch(tampung.post);
    }
    //menutup file posting yang telah dibaca
    fclose(tampil);
}
//prosedur fitur tambah posting
void tambahkanpost()
{
    //membersihkan layar sebelumnya
    system("cls");
    system("title Dashboard / Post / Tambah - DinusBlog");
    printf("--------------------------------------------------------------------------------\n");
    printf("                                   DINUSBLOG\n");
    printf("                        - Simplicity Blog with C CMS -\n");
    printf("\n--------------------------------------------------------------------------------\n\n");
    printf(" Judul : ");
    //membersihkan inputan sebelumnya
    fflush(stdin);
    //inputann judul posting yang akan ditambah
    gets(isijudul);
    printf("\n Isi Postingan :\n");
    //menampung alamat file yang akan dibuat
    sprintf(url.post,"db/post/%s/%s",tampung.user,isijudul);
    //memastikan file postingan dapat dibuat
    if((tambah=fopen(url.post,"w")) == NULL)
    {
        puts("Postingan tidak dapat dibuat!\r\n");
    }
    //looping untuk menulis sampai enter ditekan
    printf(" ");
    while((tampung.konten=getche())!=13)
    {
        //memasukkan inputan ke dalam file
        fputc(tampung.konten,tambah);
    }
    //menutup file yang telah diibuat
    fclose(tambah);
    printf("\n\n                          Posting telah ditambahkan!");
}
//prosedur fitur hapus postingan
void hapuspost()
{
    //membersihkan layar sebelumnya
    system("cls");
    system("title Dashboard / Post / Hapus - DinusBlog");
    printf("--------------------------------------------------------------------------------\n");
    printf("                                   DINUSBLOG\n");
    printf("                        - Simplicity Blog with C CMS -\n");
    printf("\n--------------------------------------------------------------------------------\n\n");
    printf("\n Daftar postingan anda :\n");
    printf(" +----------------------------------------------------- \n");
    //menampung alamat postingan user
    sprintf(url.hapuspost,"post/%s",tampung.user);
    //menampilkan list postingan
    tampilkanfile(url.hapuspost);
    printf("\n Masukkan nomor postingan yang ingin dihapus : ");
    //memilih nomor urut postingan
    scanf("%d",&pilihpost);
    sprintf(url.hapuspost,"db/post/%s",tampung.user);
    //membuka folder
    folder = opendir(url.hapuspost);
    if (folder)
    {
        i=-1;
        //membaca isi folder dan memastikan foldernya ada
        while ((dir = readdir(folder)) != NULL)
        {
            //memilih podtingan sesuai nomor urut yang dilooping
            if(pilihpost==i)
            {
                //menampung alamat posting yang akan dihapus
                sprintf(url.post,"db/post/%s/%s",tampung.user,dir->d_name);
                //menyalin judul postingan
                strcpy(tampung.judulpost,dir->d_name);
            }
            i=i+1;
        }
        //menutup folder yang telah dibuka
        closedir(folder);
    }
    //membersihkan layar sebelumnya
    system("cls");
    //menghapud file posting dan melihat status penghapusan
    statushapus=remove(url.post);
    printf("--------------------------------------------------------------------------------\n");
    printf("                                   DINUSBLOG\n");
    printf("                        - Simplicity Blog with C CMS -\n");
    printf("\n--------------------------------------------------------------------------------\n\n");
    //jika file terhapus(mengeluarkan angka 0 jika berhasil)
    if(statushapus == 0)
    {
        sprintf(tampung.tengah,"Posting %s telah dihapus.",tampung.judulpost);
        printf("\n%*s\n\n", 40+strlen(tampung.tengah)/2, strupr(tampung.tengah), 40-strlen(tampung.tengah)/2, "");
    }
    //jika file gagal dihapus
    else
    {
        sprintf(tampung.tengah,"Posting %s gagal dihapus.",tampung.judulpost);
        printf("\n%*s\n\n", 40+strlen(tampung.tengah)/2, tampung.tengah, 40-strlen(tampung.tengah)/2, "");
    }
}
