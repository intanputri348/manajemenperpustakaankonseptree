#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Buku {
    int id;
    string judul;
    string penulis;
    string penerbit;
    Buku* left;
    Buku* right;
    int height;
};

class BukuPerpustakaan {
private:
    Buku* rootBST;
    Buku* rootAVL;
    const string csvFileBST = "buku_bst.csv";
    const string csvFileAVL = "buku_avl.csv";

public:
    BukuPerpustakaan() {
        rootBST = nullptr;
        rootAVL = nullptr;
    }

    Buku* tambahBST(Buku* root, int id, const string& judul, const string& penulis, const string& penerbit) {
        if (root == nullptr) {
            Buku* newBuku = new Buku();
            newBuku->id = id;
            newBuku->judul = judul;
            newBuku->penulis = penulis;
            newBuku->penerbit = penerbit;
            newBuku->left = newBuku->right = nullptr;
            return newBuku;
        }

        if (id < root->id)
            root->left = tambahBST(root->left, id, judul, penulis, penerbit);
        else if (id > root->id)
            root->right = tambahBST(root->right, id, judul, penulis, penerbit);

        return root;
    }

    Buku* tambahAVL(Buku* root, int id, const string& judul, const string& penulis, const string& penerbit) {
        if (root == nullptr) {
            Buku* newBuku = new Buku();
            newBuku->id = id;
            newBuku->judul = judul;
            newBuku->penulis = penulis;
            newBuku->penerbit = penerbit;
            newBuku->left = newBuku->right = nullptr;
            newBuku->height = 1;
            return newBuku;
        }

        if (id < root->id)
            root->left = tambahAVL(root->left, id, judul, penulis, penerbit);
        else if (id > root->id)
            root->right = tambahAVL(root->right, id, judul, penulis, penerbit);
        else
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && id < root->left->id)
            return rotateRight(root);

        if (balance < -1 && id > root->right->id)
            return rotateLeft(root);

        if (balance > 1 && id > root->left->id) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && id < root->right->id) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    int getHeight(Buku* root) {
        return root == nullptr ? 0 : root->height;
    }

    int getBalance(Buku* node) {
        return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    Buku* rotateRight(Buku* y) {
        Buku* x = y->left;
        Buku* T = x->right;

        x->right = y;
        y->left = T;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Buku* rotateLeft(Buku* x) {
        Buku* y = x->right;
        Buku* T = y->left;

        y->left = x;
        x->right = T;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    void tampilkanMenuBST() {
        cout << "---------------------------------------------------------------------" << endl;
        cout << "| ID  |      Judul         |      Penulis       |      Penerbit     |" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        tampilkanBST(rootBST);
        cout << "---------------------------------------------------------------------" << endl;
    }

    void tampilkanMenuAVL() {
        cout << "---------------------------------------------------------------------" << endl;
        cout << "| ID  |       Judul        |       Penulis      |      Penerbit     |" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        tampilkanAVL(rootAVL);
        cout << "---------------------------------------------------------------------" << endl;
    }

    void tampilkanBST(Buku* root) {
        if (root == nullptr) return;
        tampilkanBST(root->left);
        cout << "|" << setw(5) << left << root->id << "|"
             << setw(20) << left << root->judul << "|"
             << setw(20) << left << root->penulis << "|"
             << setw(19) << left << root->penerbit << "|" << endl;
        tampilkanBST(root->right);
    }

    void tampilkanAVL(Buku* root) {
        if (root == nullptr) return;
        tampilkanAVL(root->left);
        cout << "|" << setw(5) << root->id << "|"
             << setw(20) << left << root->judul << "|"
             << setw(20) << left << root->penulis << "|"
             << setw(19) << left << root->penerbit << "|" << endl;
        tampilkanAVL(root->right);
    }

    void tambahBuku(int id, const string& judul, const string& penulis, const string& penerbit, int pilihan) {
        if (pilihan == 1) {
            rootBST = tambahBST(rootBST, id, judul, penulis, penerbit);
        } else if (pilihan == 2) {
            rootAVL = tambahAVL(rootAVL, id, judul, penulis, penerbit);
        }
    }

    void cariBuku(int id, int pilihan) {
        Buku* hasil = nullptr;
        if (pilihan == 1) {
            hasil = cariBST(rootBST, id);
        } else if (pilihan == 2) {
            hasil = cariAVL(rootAVL, id);
        }

        if (hasil != nullptr) {
            cout << "Buku dengan ID " << id << " ditemukan." << endl;
            cout << "---------------------------------------------------------------------" << endl;
            cout << "| ID  |      Judul      |      Penulis      |        Penerbit       |" << endl;
            cout << "---------------------------------------------------------------------" << endl;
            cout << "|" << setw(5) << hasil->id << "|"
                 << setw(17) << hasil->judul <<    "|"
                 << setw(19) << hasil->penulis <<  "|"
                 << setw(23) << hasil->penerbit << "|" << endl;
            cout << "---------------------------------------------------------------------" << endl;
        } else {
            cout << "Buku dengan ID " << id << " tidak ditemukan." << endl;
        }
    }

    Buku* cariBST(Buku* root, int id) {
        if (root == nullptr || root->id == id)
            return root;
        if (id < root->id)
            return cariBST(root->left, id);
        else
            return cariBST(root->right, id);
    }

    Buku* cariAVL(Buku* root, int id) {
        if (root == nullptr || root->id == id)
            return root;
        if (id < root->id)
            return cariAVL(root->left, id);
        else
            return cariAVL(root->right, id);
    }

    Buku* findMin(Buku* root) {
        while (root->left != nullptr)
            root = root->left;
        return root;
    }

    Buku* deleteNodeBST(Buku* root, int id) {
        if (root == nullptr)
            return root;

        if (id < root->id)
            root->left = deleteNodeBST(root->left, id);
        else if (id > root->id)
            root->right = deleteNodeBST(root->right, id);
        else {
            if (root->left == nullptr) {
                Buku* temp = root ->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Buku* temp = root->left;
                delete root;
                return temp;
            }

            Buku* temp = findMin(root->right);
            root->id = temp->id;
            root->judul = temp->judul;
            root->penulis = temp->penulis;
            root->penerbit = temp->penerbit;

            root->right = deleteNodeBST(root->right, temp->id);
        }
        return root;
    }

    Buku* deleteNodeAVL(Buku* root, int id) {
        if (root == nullptr)
            return root;

        if (id < root->id)
            root->left = deleteNodeAVL(root->left, id);
        else if (id > root->id)
            root->right = deleteNodeAVL(root->right, id);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Buku* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Buku* temp = findMin(root->right);
                root->id = temp->id;
                root->judul = temp->judul;
                root->penulis = temp->penulis;
                root->penerbit = temp->penerbit;

                root->right = deleteNodeAVL(root->right, temp->id);
            }
        }

        if (root == nullptr)
            return root;

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void simpanDataKeCSV(Buku* root, const string& fileName) {
        ofstream file(fileName);
        if (file.is_open()) {
            saveToCSV(root, file);
            file.close();
        }
    }

    void saveToCSV(Buku* root, ofstream& file) {
        if (root != nullptr) {
            file << root->id << "," << root->judul << "," << root->penulis << "," << root->penerbit << "\n";
            saveToCSV(root->left, file);
            saveToCSV(root->right, file);
        }
    }

    void muatDataDariCSV(Buku*& root, const string& fileName, int pilihan) {
        ifstream file(fileName);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string judul, penulis, penerbit;
            char delimiter;
            ss >> id >> delimiter;
            getline(ss, judul, ',');
            getline(ss, penulis, ',');
            getline(ss, penerbit);

            tambahBuku(id, judul, penulis, penerbit, pilihan);
        }
    }

    void pilihTree() {
        int pilihan;
        while (true) {
            cout << "\n==========================================\n";
            cout << "|             SELAMAT DATANG             |\n";
            cout << "|  di Sistem Manajemen Buku Perpustakaan |\n";
            cout << "==========================================\n";
            cout << "|              Metode Tree               |\n";
            cout << "|----------------------------------------|\n";
            cout << "|  No |           Metode                 |\n";
            cout << "|----------------------------------------|\n";
            cout << "|  1  | Binary Search Tree (BST)         |\n";
            cout << "|  2  | AVL Tree                         |\n";
            cout << "|  3  | Keluar                           |\n";
            cout << "------------------------------------------\n";
            cout << "Metode Pilihan: ";
            cin >> pilihan;

            if (pilihan == 1 || pilihan == 2) {
                muatDataDariCSV((pilihan == 1) ? rootBST : rootAVL, (pilihan == 1) ? csvFileBST : csvFileAVL, pilihan);
                menuBuku(pilihan);
            } else if (pilihan == 3) {
                simpanDataKeCSV(rootBST, csvFileBST);
                simpanDataKeCSV(rootAVL, csvFileAVL);
                cout << "Data telah disimpan ke file CSV." << endl;
                cout << "Terima Kasih Sudah Menggunakan Sistem Ini, Sampai Jumpa Kembali.\n";
                break;
            } else {
                cout << "Pilihan tidak valid. Coba lagi.\n";
            }
        }
    }

    void menuBuku(int pilihan) {
        int subMenu, id;
        string judul, penulis, penerbit;

        string judulMenu = (pilihan == 1) ? "MENU BST" : "MENU AVL";

        while (true) {
            cout << "\n------------------------------------\n";
            cout << "|==========   " << judulMenu << "   ==========|\n";
            cout << "------------------------------------\n";
            cout << "| Pilihan |          Menu          |\n";
            cout << "------------------------------------\n";
            cout << "|    1    | Tambah Buku            |\n";
            cout << "|    2    | Tampilkan Data Buku    |\n";
            cout << "|    3    | Cari Buku              |\n";
            cout << "|    4    | Hapus Buku             |\n";
            cout << "|    5    | Kembali                |\n";
            cout << "------------------------------------\n";
            cout << "Pilih: ";
            cin >> subMenu;

            if (subMenu == 1) {
                cout << "Masukkan ID Buku      : ";
                cin >> id;
                cin.ignore();
                cout << "Masukkan Judul Buku   : ";
                getline(cin, judul);
                cout << "Masukkan Penulis Buku : ";
                getline(cin, penulis);
                cout << "Masukkan Penerbit Buku: ";
                getline(cin, penerbit);
                tambahBuku(id, judul, penulis, penerbit, pilihan);
            } else if (subMenu == 2) {
                if (pilihan == 1) {
                    tampilkanMenuBST();
                } else if (pilihan == 2) {
                    tampilkanMenuAVL();
                }
            } else if (subMenu == 3) {
                cout << "Masukkan ID Buku yang ingin dicari: ";
                cin >> id;
                cariBuku(id, pilihan);
            } else if (subMenu == 4) {
                cout << "Masukkan ID Buku yang ingin dihapus: ";
                cin >> id;
                if (pilihan == 1) {
                    rootBST = deleteNodeBST(rootBST, id);
                    cout << "Buku dengan ID " << id << " telah dihapus dari BST.\n";
                } else if (pilihan == 2) {
                    rootAVL = deleteNodeAVL(rootAVL, id);
                    cout << "Buku dengan ID " << id << " telah dihapus dari AVL.\n";
                }
            } else if (subMenu == 5) {
                break;
            } else {
                cout << "Pilihan tidak valid. Coba lagi.\n";
            }
        }
    }
};

int main() {

    cout << "\n-------------------------------------------------------------------------";
    cout << "\n  Nama: Intan Putri Mansyur Pratama        Nama: Imelda Dwi Ariningtyas\n";
    cout << "\n  NPM:  163                                NPM:  254\n";
    cout << "-------------------------------------------------------------------------\n";

    cout << "\n=========================================================================";
    cout << "\n                         PERPUSTAKAAN RUANG KATA\n";
    cout << "\n          Selamat datang di Sistem Manajemen Buku Perpustakaan!";
    cout << "\n           Mari bersama-sama menciptakan pengalaman membaca yang";
    cout << "\n                menyenangkan dan mendukung budaya literasi";
    cout << "\n                     Selamat menggunakan sistem kami!";
    cout << "\n=========================================================================\n\n";

    BukuPerpustakaan perpustakaan;
    perpustakaan.pilihTree();
    return 0;
}
