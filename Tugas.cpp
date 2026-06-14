#include <iostream>
#include <string>
#include <vector>
using namespace std;

class pegawai{
protected:
string nama, noPegawai, jabatan;
float gaji, bonus, pajak;

public:
pegawai(string n, string no_pgw, string j){
    nama = n;
    noPegawai = no_pgw;
    jabatan = j;
    gaji = 0;
    bonus = 0;
    pajak = 0;
}

string getnama(){return nama;}
string getnopegawai(){return noPegawai;}
string getjabatan(){return jabatan;}
float getgaji(){return gaji;}
float getbonus(){return bonus;}
float getpajak(){return pajak;}

float gajibersih(){
    return (gaji + bonus) - pajak;
}

void tampilkandata(){
cout << "----- Tampilkan Data -----" << endl;
cout << "No.Pegawai        : " << getnopegawai() << endl;
cout << "Nama              : " << getnama() << endl;
cout << "Jabatan           : " << getjabatan() << endl;
cout << "Gaji Pokok        : Rp" << getgaji() << endl;
cout << "Bonus             : Rp" << getbonus() << endl;
cout << "Pajak Penghasilan : Rp" << getpajak() << endl; 
cout << "Gaji Bersih       : Rp" << gajibersih() << endl;
}

virtual void hitungfinansial() = 0;

virtual ~pegawai(){
    // Destructor untuk menghapus data Pegawai
}
};

class Komisaris : public pegawai{
public:
Komisaris(string nama, string noPegawai) : pegawai (nama, noPegawai, "Komisaris"){}

void hitungfinansial() override {
    gaji = 25000000; //Gaji komisaris 25 Juta
    bonus = 10000000; //Bonus komisaris 10 Juta
    pajak = (gaji + bonus) * 0.15; //Pajak komisaris 15%
}
};

class Direktur : public pegawai{
public:
Direktur(string nama, string noPegawai) : pegawai(nama, noPegawai, "Direktur"){}

void hitungfinansial() override {
    gaji = 20000000; //Gaji Direktur 20 Juta 
    bonus = 7500000; //Bonus Direktur 7.5 Juta
    pajak = (gaji + bonus) * 0.12; //Pajak Direktur 12 Juta
}
};

class Manajer : public pegawai{
public:
Manajer(string nama, string noPegawai) : pegawai (nama, noPegawai, "Manajer"){}

void hitungfinansial() override {
    gaji = 12000000; //Gaji Manajer 12 Juta
    bonus = 4000000; //Bonus Manajer 4 Juta
    pajak = (gaji + bonus) * 0.10; //Pajak Manajer 10%
    }
};

class Staf : public pegawai{
public:
Staf(string nama, string noPegawai) : pegawai (nama, noPegawai, "Staf"){}
    
void hitungfinansial() override {
    gaji = 5000000; //Gaji Staf 5 Juta
    bonus = 1500000; //Bonus Staf 1.5 Juta
    pajak = (gaji + bonus) * 0.05; //Pajak Manajer 5%
    }
};

int main () {
    vector<pegawai*> daftarPegawai;  //Untuk menampung database pegawai sementara
    int pilihanMenu;
    string namaPegawai, noPegawai;

    do {
        cout <<"^^^Menu Utama^^^" <<endl;
        cout <<"1. Input Data Pegawai" <<endl;
        cout <<"2. Tampilan Data" <<endl;
        cout <<"3. Keluar" <<endl;
        cout <<"Pilihan: ";
        cin >> pilihanMenu;
        cin.ignore();

        if (pilihanMenu == 1) {
            cout <<"\n---Menu Input Data Pegawai---" <<endl;
            cout <<"Masukkan Nama Pegawai: ";
            getline(cin, namaPegawai);
            cout <<"Masukkan Nomor Pegawai: ";
            getline(cin, noPegawai);

            int pilihanJabatan;
            pegawai* pegawaiBaru = nullptr;

            while (true) {  //Loop untuk validasi jabatan
                cout <<"\nDaftar Jabatan Pegawai" <<endl;
                cout <<"1. Komisaris" <<endl;
                cout <<"2. Direktur" <<endl;
                cout <<"3. Manajer" <<endl;
                cout <<"4. Staff" <<endl;
                cin >> pilihanJabatan;

                if (pilihanJabatan == 1) {
                    pegawaiBaru = new Komisaris(namaPegawai, noPegawai);
                    break;
                } else if (pilihanJabatan == 2) {
                    pegawaiBaru = new Direktur(namaPegawai, noPegawai);
                    break;
                } else if (pilihanJabatan == 3) {
                    pegawaiBaru = new Manajer(namaPegawai, noPegawai);
                    break;
                } else if (pilihanJabatan == 4) {
                    pegawaiBaru = new Staf(namaPegawai, noPegawai);
                    break;
                } else {
                    cout <<"Pesan: No Salah, Ulangi !" <<endl;
                }
            }
            if (pegawaiBaru != nullptr) { //Gabung & Simpan Data
                pegawaiBaru ->hitungfinansial();
                daftarPegawai.push_back(pegawaiBaru);
                cout <<"\nPesan: Data Pegawai Tersimpan" <<endl;
            }
        } else if (pilihanMenu == 2) {
            cout <<"\nMenu Daftar Pegawai" <<endl;
            if (daftarPegawai.empty()) {
                cout <<"Belum ada data pegawai yang tersimpan" <<endl;
            } else {
                for (size_t i = 0; i < daftarPegawai.size(); i++) {
                    cout <<"Pegawai ke-" << (i + 1) << endl;
                    daftarPegawai[i] -> tampilkandata();
                }
            }
            int subPilihan;
            cout <<"\nMau lanjut kemana?" <<endl;
            cout <<"1. Kembali ke awal (Menu)" <<endl;
            cout <<"2. Selesai (Keluar Aplikasi)" <<endl;
            cout <<"Pilihan Anda: ";
            cin >> subPilihan;

            if (subPilihan == 2) {
                cout <<"Pesan: Terimakasih Bla bla bla" <<endl;
                break;
            }
        } else if (pilihanMenu == 3) {
            cout <<"\nPesan: Terimakasih Bla bla bla" <<endl;
            break;
        } else {
            cout <<"\nPilihan anda salah. Masukkan ANGKA 1-3!\n\n";
        }
    } while (pilihanMenu != 3);

    for (auto peg : daftarPegawai) {
        delete peg;
    }
    daftarPegawai.clear();

    cout <<"\nProgram Selesai" <<endl;
    return 0;
};
