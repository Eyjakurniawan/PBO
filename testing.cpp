#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ==========================================
// 1. BASE CLASS (Encapsulation & Inheritance)
// ==========================================
class Pegawai {
private:
    string nama;
    string noPegawai;
    string jabatan;

protected:
    double gajiPokok;
    double bonus;
    double pajakPenghasilan;

public:
    Pegawai(string nama, string noPegawai, string jabatan) {
        this->nama = nama;
        this->noPegawai = noPegawai;
        this->jabatan = jabatan;
        this->gajiPokok = 0;
        this->bonus = 0;
        this->pajakPenghasilan = 0;
    }

    // Virtual Destructor
    virtual ~Pegawai() {}

    // Polymorphism: Fungsi virtual untuk menghitung finansial spesifik jabatan
    virtual void hitungFinansial() = 0; 

    // Getter untuk enkapsulasi data private
    string getNama() { return nama; }
    string getNoPegawai() { return noPegawai; }
    string getJabatan() { return jabatan; }
    double getGajiPokok() { return gajiPokok; }
    double getBonus() { return bonus; }
    double getPajak() { return pajakPenghasilan; }

    double hitungGajiBersih() {
        return (gajiPokok + bonus) - pajakPenghasilan;
    }

    // Fungsi untuk menampilkan data pegawai
    void tampilkanData() {
        cout << "-------------------------------------------\n";
        cout << "No. Pegawai       : " << noPegawai << endl;
        cout << "Nama              : " << nama << endl;
        cout << "Jabatan           : " << jabatan << endl;
        cout << "Gaji Pokok        : Rp. " << gajiPokok << endl;
        cout << "Bonus             : Rp. " << bonus << endl;
        cout << "Pajak Penghasilan : Rp. " << pajakPenghasilan << endl;
        cout << "Gaji Bersih       : Rp. " << hitungGajiBersih() << endl;
    }
};

// ==========================================
// 2. DERIVED CLASSES (Polymorphism & Multi-Inheritance style)
// ==========================================
class Komisaris : public Pegawai {
public:
    Komisaris(string nama, string noPegawai) : Pegawai(nama, noPegawai, "Komisaris") {}
    
    void hitungFinansial() override {
        gajiPokok = 25000000;
        bonus = 10000000;
        pajakPenghasilan = 0.15 * (gajiPokok + bonus); // Pajak 15%
    }
};

class Direktur : public Pegawai {
public:
    Direktur(string nama, string noPegawai) : Pegawai(nama, noPegawai, "Direktur") {}
    
    void hitungFinansial() override {
        gajiPokok = 20000000;
        bonus = 7500000;
        pajakPenghasilan = 0.12 * (gajiPokok + bonus); // Pajak 12%
    }
};

class Manajer : public Pegawai {
public:
    Manajer(string nama, string noPegawai) : Pegawai(nama, noPegawai, "Manajer") {}
    
    void hitungFinansial() override {
        gajiPokok = 12000000;
        bonus = 4000000;
        pajakPenghasilan = 0.10 * (gajiPokok + bonus); // Pajak 10%
    }
};

class Staf : public Pegawai {
public:
    Staf(string nama, string noPegawai) : Pegawai(nama, noPegawai, "Staf") {}
    
    void hitungFinansial() override {
        gajiPokok = 5000000;
        bonus = 1500000;
        pajakPenghasilan = 0.05 * (gajiPokok + bonus); // Pajak 5%
    }
};

// ==========================================
// MAIN PROGRAM (Sesuai Flowchart)
// ==========================================
int main() {
    vector<Pegawai*> daftarPegawai; // Penampung database pegawai sementara
    int pilihanMenu;
    string nama, noPeg;

    do {
        // Tampilan Menu Utama
        cout << "===========================================\n";
        cout << "               MENU UTAMA                  \n";
        cout << "===========================================\n";
        cout << "1. Input data pegawai\n";
        cout << "2. Tampilan Data\n";
        cout << "3. Keluar\n";
        cout << "-------------------------------------------\n";
        cout << "Pilihan: ";
        cin >> pilihanMenu;
        cin.ignore(); // Membersihkan buffer input

        if (pilihanMenu == 1) {
            // PROSES INPUT DATA
            
            cout << "\n--- Input Data Pegawai ---\n";
            cout << "Ketik Nama pegawai : ";
            getline(cin, nama);
            cout << "Ketik No Pegawai   : ";
            getline(cin, noPeg);
        
            int pilihanJabatan;
            Pegawai* pegawaiBaru = nullptr;

            // Loop Validasi Jabatan (Sesuai kondisi "Jabatan Sesuai?" di flowchart)
            while (true) {
                cout << "\nDaftar Jabatan Pegawai:\n";
                cout << "1. Komisaris\n";
                cout << "2. Direktur\n";
                cout << "3. Manajer\n";
                cout << "4. Staf\n";
                cout << "Pilih Jabatan (1-4): ";
                cin >> pilihanJabatan;

                if (pilihanJabatan == 1) {
                    pegawaiBaru = new Komisaris(nama, noPeg);
                    break;
                } else if (pilihanJabatan == 2) {
                    pegawaiBaru = new Direktur(nama, noPeg);
                    break;
                } else if (pilihanJabatan == 3) {
                    pegawaiBaru = new Manajer(nama, noPeg);
                    break;
                } else if (pilihanJabatan == 4) {
                    pegawaiBaru = new Staf(nama, noPeg);
                    break;
                } else {
                    // Jika Tidak Sesuai
                    cout << "Pesan: No salah, Ulangi !\n";
                }
            }

            // Gabung & Simpan Data (Serta kalkulasi otomatis via Polymorphism)
            if (pegawaiBaru != nullptr) {
                pegawaiBaru->hitungFinansial();
                daftarPegawai.push_back(pegawaiBaru);
                cout << "\nPesan: Data Pegawai Tersimpan\n\n";
            }

        } else if (pilihanMenu == 2) {
            // PROSES LIHAT DATA
            cout << "\n===========================================\n";
            cout << "             DAFTAR PEGAWAI                \n";
            cout << "===========================================\n";
            
            if (daftarPegawai.empty()) {
                cout << "Belum ada data pegawai yang tersimpan.\n";
            } else {
                for (size_t i = 0; i < daftarPegawai.size(); i++) {
                    cout << "Pegawai ke-" << (i + 1) << endl;
                    daftarPegawai[i]->tampilkanData();
                }
            }
            cout << "===========================================\n";

            // Kondisi "Mau lanjut kemana?" setelah tampil data
            int subPilihan;
            cout << "\nMau lanjut kemana?\n";
            cout << "1. Kembali ke awal (Menu)\n";
            cout << "2. Selesai (Keluar Aplikasi)\n";
            cout << "Pilihan anda: ";
            cin >> subPilihan;

            if (subPilihan == 2) {
                cout << "\nPesan : Terimakasih Bla bla bla\n";
                break; // Keluar dari loop utama dan menyudahi program
            }

        } else if (pilihanMenu == 3) {
            // Keluar langsung dari Menu Utama
            cout << "\nPesan : Terimakasih Bla bla bla\n";
            break;
        } else {
            // Validasi menu utama jika angka tidak 1-3
            cout << "\nPilihan anda salah. Masukan ANGKA 1-3!\n\n";
        }

    } while (pilihanMenu != 3);

    // Memory Cleanup (Menghapus alokasi pointer agar tidak bocor)
    for (auto peg : daftarPegawai) {
        delete peg;
    }
    daftarPegawai.clear();

    cout << "\n[Program Selesai]\n";
    return 0;
}