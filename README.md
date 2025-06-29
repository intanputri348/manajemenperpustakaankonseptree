# 📚 Sistem Manajemen Buku Perpustakaan — BST & AVL Tree

Sistem ini merupakan aplikasi berbasis C++ yang dirancang untuk membantu pengelolaan buku di perpustakaan menggunakan dua jenis struktur data pohon: **Binary Search Tree (BST)** dan **AVL Tree**. 
Sistem ini mendukung operasi seperti penambahan, pencarian, penghapusan, dan penampilan data buku, serta dilengkapi fitur penyimpanan dan pemuatan data dari file **CSV**.

---

## ✨ Fitur Utama

- ✅ Pilihan metode struktur data: **BST** atau **AVL Tree**
- ➕ Tambah data buku (ID, Judul, Penulis, Penerbit)
- 🔍 Cari buku berdasarkan ID
- 🗑️ Hapus buku dari sistem
- 📄 Simpan & muat data otomatis ke/dari file **CSV**
- 📋 Tampilkan daftar buku dalam format tabel
- 🔄 AVL Tree dengan **auto-balancing rotation** (LL, RR, LR, RL)

---

## 🧠 Konsep yang Digunakan

- **Binary Search Tree (BST)**: Struktur data pohon biner yang memungkinkan pencarian cepat berdasarkan ID buku.
- **AVL Tree**: Pohon biner seimbang yang melakukan rotasi otomatis saat terjadi ketidakseimbangan.
- **File Handling**: Data buku disimpan secara permanen dalam file CSV.
- **Object-Oriented Programming**: Implementasi berbasis kelas `BukuPerpustakaan`.

---

## 🗂️ Struktur File CSV

- Contoh isi file `buku_bst.csv` atau `buku_avl.csv`:
