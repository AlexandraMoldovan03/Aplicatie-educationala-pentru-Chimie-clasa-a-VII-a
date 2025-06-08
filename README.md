# Aplicație educațională Chimie clasa a VII-a

# Aplicație educațională – Chimie clasa a VII-a

Această aplicație este realizată ca parte a lucrării de licență și are scopul de a sprijini elevii de gimnaziu în învățarea chimiei printr-o abordare interactivă și adaptată vârstei.

## Funcționalități

- Teorie organizată pe capitole conform manualului de clasa a VII-a
- Probleme rezolvate pas cu pas (inclusiv pentru concentrații chimice)
- Teste grilă cu punctaj automat și feedback
- Jocuri educaționale (tip memory, roata norocului, drag and drop)
- Constructor de molecule cu salvare în baza de date
- Echilibrarea automată a ecuațiilor chimice
- Vizualizare progres al elevului
- Conectare utilizatori și salvare scoruri în baza de date MariaDB

## Tehnologii folosite

- Visual C++/CLI (Windows Forms)
- MariaDB pentru gestionarea datelor
- STL și operare cu fracții pentru echilibrarea reacțiilor
- Drag & Drop și interfețe animate pentru interactivitate
- Interfață personalizată, optimizată pentru uz educațional

## Cum rulezi aplicația

### 1. Descărcare

Clonează repository-ul sau descarcă arhiva:
```bash
git clone https://github.com/utilizator/aplicatie-chimie-licenta.git
```

### 2. Instalare MariaDB

- Descarcă și instalează MariaDB de la: [https://mariadb.org/download/](https://mariadb.org/download/)
- Creează o bază de date nouă și importă fișierul `dump.sql` inclus în acest repository:

```bash
mysql -u root -p < dump.sql
```

> Asigură-te că datele de conectare din cod (`username`, `password`, `nume_baza_de_date`) corespund configurației locale.

### 3. Compilare și rulare

- Deschide soluția `.sln` în **Visual Studio**
- Selectează configurația `Release` sau `Debug`
- Apasă pe **Start** (sau F5) pentru a compila și rula aplicația

##Conținut proiect

```
├── src/
│   ├── main.cpp
│   ├── MoleculeBuilder.cpp
│   ├── ConcentratieForm.cpp
│   ├── ReactionSolver.cpp
│   └── ...
├── res/
│   ├── imagini/
│   └── pdf/Manual-Chimie-clasa7.pdf
├── dump.sql
├── README.md
└── Licenta.pdf
```

## Exemple de utilizare

- **Echilibrare reacții:** Introdu `H2 + O2 -> H2O` → aplicația oferă rezultatul `2H2 + O2 = 2H2O` și o explicație.
- **Constructor molecule:** Trage atomi și formează `H2O`, aplicația recunoaște molecula și o salvează.
- **Testare:** Răspunde la întrebări din test și primești punctajul imediat.

## Contribuții proprii

- Interfață grafică extinsă în Visual C++/CLI
- Algoritm propriu pentru echilibrarea ecuațiilor pe bază de matrici și fracții
- Jocuri educaționale dezvoltate de la zero
- Integrare MariaDB și salvare progres utilizatori

## Licență

Proiect realizat pentru lucrarea de licență – [Universitatea de Vest din Timișoara], Facultatea de Matematică și Informatică.
