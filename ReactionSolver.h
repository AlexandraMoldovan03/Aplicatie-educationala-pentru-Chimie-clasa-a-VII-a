#pragma once
#pragma execution_character_set("utf-8")

// Include biblioteci standard C++
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>


// Pentru conversii între System::String^ și std::string
#include <msclr/marshal_cppstd.h>
using namespace System::Windows::Forms;
namespace LicentaChimie {

    const std::set<std::string> validElements = {
    "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si",
    "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co",
    "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y",
    "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb",
    "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu",
    "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re",
    "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr",
    "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es",
    "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg",
    "Cn", "Fl", "Lv", "Ts", "Og"
    };




    // Clasa Fraction pentru aritmetică exactă
    class Fraction {
    public:
        long long num, den;
        Fraction(long long n = 0, long long d = 1) {
            if (d == 0) { throw std::runtime_error("Denom cannot be zero"); }
            num = n;
            den = d;
            normalize();
        }
        void normalize() {
            if (den < 0) { num = -num; den = -den; }
            long long g = gcd(llabs(num), llabs(den));
            if (g != 0) { num /= g; den /= g; }
        }
        static long long gcd(long long a, long long b) {
            return b == 0 ? a : gcd(b, a % b);
        }
        Fraction operator+(const Fraction& other) const {
            return Fraction(num * other.den + other.num * den, den * other.den);
        }
        Fraction operator-(const Fraction& other) const {
            return Fraction(num * other.den - other.num * den, den * other.den);
        }
        Fraction operator*(const Fraction& other) const {
            return Fraction(num * other.num, den * other.den);
        }
        Fraction operator/(const Fraction& other) const {
            return Fraction(num * other.den, den * other.num);
        }
    };

    // Funcție pentru parsarea formulei chimice (ex: "H2O")
    inline std::map<std::string, int> parseFormula(const std::string& formula) {
        std::map<std::string, int> elemCount;

        for (size_t i = 0; i < formula.size(); ) {
            if (!isalpha(formula[i])) {
                i++;
                continue;
            }

            std::string symbol;
            symbol += formula[i];
            if (i + 1 < formula.size() && islower(formula[i + 1])) {
                symbol += formula[i + 1];
            }

            // Verificăm dacă simbolul extins (ex: "He") este valid
            if (validElements.count(symbol)) {
                i += symbol.length();
            }
            else if (validElements.count(std::string(1, formula[i]))) {
                symbol = std::string(1, formula[i]);
                i++;
            }
            else {
                throw std::runtime_error("Element necunoscut: " + symbol);
            }

            // Citim numărul (dacă există)
            int count = 0;
            while (i < formula.size() && isdigit(formula[i])) {
                count = count * 10 + (formula[i] - '0');
                i++;
            }
            if (count == 0) count = 1;

            elemCount[symbol] += count;
        }

        return elemCount;
    }

    // Funcție utilă: separă un șir după un delimitator
    inline std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> tokens;
        std::istringstream iss(s);
        std::string token;
        while (getline(iss, token, delim)) {
            token.erase(token.begin(), std::find_if(token.begin(), token.end(), [](unsigned char ch) { return !std::isspace(ch); }));
            token.erase(std::find_if(token.rbegin(), token.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), token.end());
            if (!token.empty())
                tokens.push_back(token);
        }
        return tokens;
    }

    // Funcție care echilibrează ecuația chimică
    inline std::vector<long long> balanceEquation(const std::vector<std::string>& reactants, const std::vector<std::string>& products) {
        int n_reactants = reactants.size();
        int n_products = products.size();
        int n = n_reactants + n_products;

        // Combinăm toate formulele chimice într-un singur vector
        std::vector<std::string> formulas = reactants;
        formulas.insert(formulas.end(), products.begin(), products.end());

        // Parsează fiecare formulă și colectează elementele unice
        std::set<std::string> elementSet;
        std::vector<std::map<std::string, int>> compounds;
        for (const auto& f : formulas) {
            auto m = parseFormula(f);
            compounds.push_back(m);
            for (const auto& kv : m)
                elementSet.insert(kv.first);
        }

        std::vector<std::string> elements(elementSet.begin(), elementSet.end());
        int m_rows = elements.size();

        // Construim matricea A (m_rows x n)
        std::vector<std::vector<Fraction>> A(m_rows, std::vector<Fraction>(n, Fraction(0)));

        for (int j = 0; j < n; j++) {
            for (const auto& entry : compounds[j]) {
                int row = std::distance(elements.begin(), std::find(elements.begin(), elements.end(), entry.first));
                int cnt = entry.second;
                A[row][j] = (j < n_reactants) ? Fraction(cnt) : Fraction(-cnt);
            }
        }

        // Eliminare Gaussiană
        int rank = 0;
        for (int c = 0; c < n; c++) {
            int pivotRow = rank;
            while (pivotRow < m_rows && A[pivotRow][c].num == 0) pivotRow++;
            if (pivotRow == m_rows) continue;

            std::swap(A[rank], A[pivotRow]);
            Fraction pivotVal = A[rank][c];
            for (int j = c; j < n; j++) {
                A[rank][j] = A[rank][j] / pivotVal;
            }

            for (int i = 0; i < m_rows; i++) {
                if (i != rank) {
                    Fraction factor = A[i][c];
                    for (int j = c; j < n; j++) {
                        A[i][j] = A[i][j] - factor * A[rank][j];
                    }
                }
            }
            rank++;
        }

        // Verificare soluție ne-trivială
        if (n - rank < 1) return std::vector<long long>();

        // Setăm variabilele libere la 1
        std::vector<Fraction> x(n, Fraction(1));
        for (int i = rank - 1; i >= 0; i--) {
            Fraction sum(0);
            for (int j = i + 1; j < n; j++) {
                sum = sum + A[i][j] * x[j];
            }
            x[i] = Fraction(-sum.num, sum.den);
        }

        // Convertim coeficienții în întregi
        long long lcmDen = 1;
        for (int j = 0; j < n; j++) {
            long long d = x[j].den;
            long long g = Fraction::gcd(lcmDen, d);
            lcmDen = (lcmDen / g) * d;
        }

        std::vector<long long> coeffs(n);
        for (int j = 0; j < n; j++) {
            coeffs[j] = x[j].num * (lcmDen / x[j].den);
        }

        // Asigurăm coeficienți pozitivi
        if (*std::min_element(coeffs.begin(), coeffs.end()) < 0) {
            for (long long& coef : coeffs) coef = -coef;
        }

        return coeffs;
    }


    /// <summary>
    /// Formularul ReactionSolver
    /// </summary>
    public ref class ReactionSolver : public System::Windows::Forms::Form
    {
    public:
        ReactionSolver(void)
        {
            InitializeComponent();
           
        }

    protected:
    
        ~ReactionSolver()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::TextBox^ textBoxEquation;
        System::Windows::Forms::Button^ buttonSolve;
        System::Windows::Forms::Label^ labelResult;
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Label^ labelExplanation;
        System::Windows::Forms::Label^ labelTitle;

        System::Windows::Forms::Panel^ panelExplanation;
        bool isDragging = false;
        System::Drawing::Point lastCursorPos;
        System::Drawing::Point lastPanelPos;


#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->WindowState = FormWindowState::Maximized;

            this->textBoxEquation = (gcnew System::Windows::Forms::TextBox());
            this->buttonSolve = (gcnew System::Windows::Forms::Button());
            this->labelResult = (gcnew System::Windows::Forms::Label());
            this->panelExplanation = (gcnew System::Windows::Forms::Panel());
            this->labelExplanation = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();



            // Creăm un Panel mai mare pentru explicație
            this->panelExplanation->Location = System::Drawing::Point(600, 20); // Poziționat corect
            this->panelExplanation->Size = System::Drawing::Size(500, 350); // Dimensiune mărită
            this->panelExplanation->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panelExplanation->BackColor = System::Drawing::Color::White; // Fundal alb pentru claritate
            this->panelExplanation->Padding = System::Windows::Forms::Padding(10, 35, 10, 10); // Adaugă un padding de 35px sus


            // Label pentru explicație (mărit)
            this->labelExplanation->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
            this->labelExplanation->Location = System::Drawing::Point(10, 40);
            this->labelExplanation->Size = System::Drawing::Size(480, 330); // Ajustat să încapă în Panel
            this->labelExplanation->AutoSize = false;
            this->labelExplanation->TextAlign = System::Drawing::ContentAlignment::TopLeft;
            this->labelExplanation->Text = L"Echilibrarea ecuațiilor chimice presupune ajustarea coeficienților astfel încât "
                L"numărul de atomi din fiecare element să fie egal pe ambele părți ale reacției.\n\n"
                L"Pentru a echilibra o ecuație, trebuie să comparăm numărul de atomi ai fiecărui element "
                L"și să ajustăm coeficienții pentru a asigura conservarea masei.\n\n"
                L"Introdu o ecuație chimică și apasă 'Rezolvă'.\n\n"
                L"Exemplu: H2 + O2 -> H2O. Programul va calcula coeficienții necesari pentru ca "
                L"numărul de atomi de H și O să fie egal pe ambele părți.";
            // Adăugăm label-ul în Panel
            this->panelExplanation->Controls->Add(this->labelExplanation);

            // Adăugăm panel-ul în formular
            this->Controls->Add(this->panelExplanation);


            // 
            // textBoxEquation
            // 
            this->textBoxEquation->Font = (gcnew System::Drawing::Font(L"Arial", 14));
            this->textBoxEquation->Location = System::Drawing::Point(20, 20);
            this->textBoxEquation->Size = System::Drawing::Size(800, 35);
            this->textBoxEquation->Text = L"H3PO4 + Mg(OH)2 -> Mg3(PO4)2 + H2O";
            // 
            // buttonSolve
            // 
            this->buttonSolve->Font = (gcnew System::Drawing::Font(L"Arial", 14, System::Drawing::FontStyle::Bold));
            this->buttonSolve->Location = System::Drawing::Point(20, 70);
            this->buttonSolve->Size = System::Drawing::Size(200, 50);
            this->buttonSolve->Text = L"Rezolvă";
            this->buttonSolve->UseVisualStyleBackColor = true;
            this->buttonSolve->Click += gcnew System::EventHandler(this, &ReactionSolver::buttonSolve_Click);
            // 
            // labelResult
            // 
            //this->labelResult->Font = (gcnew System::Drawing::Font(L"Arial", 12));
            //this->labelResult->Location = System::Drawing::Point(20, 130);
            //this->labelResult->Size = System::Drawing::Size(1000, 50);
            //this->labelResult->Text = L"";
            //this->labelResult->AutoSize = true;
            //this->labelResult->MaximumSize = System::Drawing::Size(1100, 0); // Se ajustează doar pe lățime
// Label pentru rezultat
            this->labelResult->Font = (gcnew System::Drawing::Font(L"Arial", 12));
            this->labelResult->Location = System::Drawing::Point(20, 140);
            this->labelResult->Size = System::Drawing::Size(600, 150);
            this->labelResult->AutoSize = true;


            // Creăm un Panel pentru explicație
            this->panelExplanation->Location = System::Drawing::Point(700, 50); // Mutăm mai la dreapta
            this->panelExplanation->AutoSize = true; // Se mărește automat în funcție de conținut
            this->panelExplanation->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->panelExplanation->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            // Adăugăm evenimentele pentru mutare
            this->panelExplanation->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ReactionSolver::panelExplanation_MouseDown);
            this->panelExplanation->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &ReactionSolver::panelExplanation_MouseMove);
            this->panelExplanation->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ReactionSolver::panelExplanation_MouseUp);

            // Creăm un label pentru titlu
            this->labelTitle = (gcnew System::Windows::Forms::Label());
            //this->labelTitle->Text = L" Explicații ";
            this->labelTitle->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
            this->labelTitle->ForeColor = System::Drawing::Color::White;
            this->labelTitle->BackColor = System::Drawing::Color::RoyalBlue; // Albastru mai închis pentru claritate
            this->labelTitle->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->labelTitle->Dock = System::Windows::Forms::DockStyle::Right;
            this->labelTitle->Width = 10; // O bară subțire pe marginea dreaptă
            this->labelTitle->Height = 30;
            this->labelTitle->Padding = System::Windows::Forms::Padding(10, 5, 0, 5);

            // Adaugă evenimentele de mutare la label (același mecanism ca la panel)
            this->labelTitle->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ReactionSolver::panelExplanation_MouseDown);
            this->labelTitle->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &ReactionSolver::panelExplanation_MouseMove);
            this->labelTitle->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ReactionSolver::panelExplanation_MouseUp);

            // Adăugăm titlul în panel
            this->panelExplanation->Controls->Add(this->labelTitle);







            // Label pentru explicație
            this->labelExplanation->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));
            this->labelExplanation->Location = System::Drawing::Point(10, 10);
            // Setează dimensiunea corectă pentru label
            this->labelExplanation->AutoSize = true;
            this->labelExplanation->AutoSize = false;
            this->labelExplanation->TextAlign = System::Drawing::ContentAlignment::TopLeft;
            
            this->labelExplanation->Text = L"Echilibrarea ecuațiilor chimice presupune ajustarea coeficienților astfel încât "
                L"numărul de atomi din fiecare element să fie egal pe ambele părți ale reacției.\n\n"
                L"Introdu o ecuație chimică și apasă 'Rezolvă'.";



            // 
            // Echilibrarea ecuatiilor
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1200, 600); // Dimensiune mai mare
            this->BackColor = System::Drawing::Color::FromArgb(0xDB, 0xE7, 0xF3);




            this->panelExplanation->Controls->Add(this->labelExplanation);
            this->Controls->Add(this->panelExplanation);
            this->Controls->Add(this->textBoxEquation);
            this->Controls->Add(this->buttonSolve);
            this->Controls->Add(this->labelResult);

            this->Name = L"ReactionSolver";
            this->Text = L"Egalizarea reacțiilor chimice";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion




           // Când apăsăm pe panel, salvăm poziția
private: System::Void panelExplanation_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
    isDragging = true;
    lastCursorPos = Cursor->Position;  // Coordonatele globale ale cursorului
    lastPanelPos = panelExplanation->Location;  // Poziția inițială a panelului
}

       // Când mutăm mouse-ul, mișcăm panel-ul dacă e apăsat
private: System::Void panelExplanation_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
    if (isDragging) {
        // Calculăm noua poziție bazată pe mișcarea cursorului
        System::Drawing::Point newCursorPos = Cursor->Position;
        System::Drawing::Point delta(
            newCursorPos.X - lastCursorPos.X,
            newCursorPos.Y - lastCursorPos.Y
        );

        panelExplanation->Location = System::Drawing::Point(
            lastPanelPos.X + delta.X,
            lastPanelPos.Y + delta.Y
        );
    }
}

       // Când ridicăm mouse-ul, oprim mutarea
private: System::Void panelExplanation_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
    isDragging = false;
}







    private: System::Void buttonSolve_Click(System::Object^ sender, System::EventArgs^ e) {
        // 1. Preluăm ecuația introdusă de utilizator
        System::String^ eqInput = this->textBoxEquation->Text;
        std::string eq = msclr::interop::marshal_as<std::string>(eqInput);

        // 2. Separa ecuația în reactanți și produși folosind "->"
        size_t pos = eq.find("->");
        if (pos == std::string::npos) {
            this->labelResult->Text = L"Ecuație invalidă. Lipseste '->'.";
            return;
        }
        std::string left = eq.substr(0, pos);
        std::string right = eq.substr(pos + 2);

        // 3. Separăm reactanții și produșii după "+"
        std::vector<std::string> reactants = split(left, '+');
        std::vector<std::string> products = split(right, '+');

        // 4. Calculăm coeficienții de echilibrare
        std::vector<long long> coeffs = balanceEquation(reactants, products);
        if (coeffs.empty()) {
            this->labelResult->Text = L"Nu s-a găsit o soluție ne-trivială.";
            return;
        }

        // 5. Construim rezultatul echilibrat
        std::ostringstream oss;
        // Reactanți
        for (size_t i = 0; i < reactants.size(); i++) {
            if (coeffs[i] != 1)
                oss << coeffs[i];
            oss << reactants[i];
            if (i < reactants.size() - 1)
                oss << " + ";
        }
        oss << " = ";
        // Produși
        for (size_t i = reactants.size(); i < coeffs.size(); i++) {
            if (coeffs[i] != 1)
                oss << coeffs[i];
            oss << products[i - reactants.size()];
            if (i < coeffs.size() - 1)
                oss << " + ";
        }

        std::string balancedEquation = oss.str();

        // 6. Generăm explicația despre echilibrare
        std::ostringstream explanation;
        explanation << "\n\nExplicație despre echilibrare:\n";

        std::map<std::string, int> reactantAtoms, productAtoms;

        // Contorizăm atomii din reactanți
        for (size_t i = 0; i < reactants.size(); i++) {
            auto atoms = parseFormula(reactants[i]);
            for (auto& kv : atoms) {
                reactantAtoms[kv.first] += kv.second * coeffs[i];
            }
        }

        // Contorizăm atomii din produși
        for (size_t i = 0; i < products.size(); i++) {
            auto atoms = parseFormula(products[i]);
            for (auto& kv : atoms) {
                productAtoms[kv.first] += kv.second * coeffs[i + reactants.size()];
            }
        }

        // Comparăm numărul de atomi de pe ambele părți
        for (const auto& kv : reactantAtoms) {
            int reactantCount = kv.second;
            int productCount = productAtoms[kv.first];

            if (reactantCount > productCount) {
                explanation << "- Inițial, existau **" << reactantCount << "** atomi de **" << kv.first
                    << "** în reactanți, dar doar **" << productCount << "** în produși. "
                    << "Așadar, s-au adăugat coeficienți pentru a echilibra numărul de atomi.\n";
            }
            else if (reactantCount < productCount) {
                explanation << "- Inițial, existau doar **" << reactantCount << "** atomi de **" << kv.first
                    << "** în reactanți, dar **" << productCount << "** în produși. "
                    << "Coeficienții au fost ajustați pentru a menține egalitatea.\n";
            }
            else {
                explanation << "- Numărul de atomi de **" << kv.first
                    << "** este deja echilibrat: **" << reactantCount << "** pe ambele părți.\n";
            }
        }

        std::string fullResult = "Reacția echilibrată:\n" + balancedEquation + explanation.str();

        // 7. Afișăm rezultatul și explicația
        this->labelResult->Text = gcnew System::String(fullResult.c_str(), 0, fullResult.length(), System::Text::Encoding::UTF8);

    }

    };
}
