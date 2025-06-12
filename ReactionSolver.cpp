#include "ReactionSolver.h"


using namespace System;
using namespace System::Windows::Forms;



//
//#include <iostream>
//#include <algorithm>
//#include <msclr/marshal_cppstd.h>
//
//using namespace LicentaChimie;
//
//// Lista elementelor chimice
//const std::set<std::string> ELEMENTS = {
//    "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S",
//    "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga",
//    "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd",
//    "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm",
//    "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os",
//    "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa",
//    "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg",
//    "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Nh", "Fl", "Mc", "Lv", "Ts", "Og"
//};
//
//// Func?ie pentru ini?ializarea UI
//void ReactionSolver::InitializeComponent(void) {
//    this->textBoxEquation = gcnew TextBox();
//    this->buttonSolve = gcnew Button();
//    this->labelResult = gcnew Label();
//    this->panelExplanation = gcnew Panel();
//    this->labelExplanation = gcnew Label();
//    this->SuspendLayout();
//
//    // Textbox pentru ecua?ie
//    this->textBoxEquation->Font = gcnew System::Drawing::Font(L"Arial", 14);
//    this->textBoxEquation->Location = Point(20, 20);
//    this->textBoxEquation->Size = System::Drawing::Size(800, 35);
//    this->textBoxEquation->Text = L"H2 + O2 -> H2O";
//
//    // Buton "Rezolv?"
//    this->buttonSolve->Font = gcnew System::Drawing::Font(L"Arial", 14, FontStyle::Bold);
//    this->buttonSolve->Location = Point(20, 70);
//    this->buttonSolve->Size = System::Drawing::Size(200, 50);
//    this->buttonSolve->Text = L"Rezolv?";
//    this->buttonSolve->Click += gcnew EventHandler(this, &ReactionSolver::buttonSolve_Click);
//
//    // Label pentru rezultat
//    this->labelResult->Font = gcnew System::Drawing::Font(L"Arial", 12);
//    this->labelResult->Location = Point(20, 140);
//    this->labelResult->Size = System::Drawing::Size(1000, 100);
//
//    // Panel pentru explica?ii
//    this->panelExplanation->Location = Point(650, 20);
//    this->panelExplanation->Size = System::Drawing::Size(350, 200);
//    this->panelExplanation->BorderStyle = BorderStyle::FixedSingle;
//
//    // Label pentru explica?ie
//    this->labelExplanation->Font = gcnew System::Drawing::Font(L"Arial", 11, FontStyle::Bold);
//    this->labelExplanation->Location = Point(10, 10);
//    this->labelExplanation->Size = System::Drawing::Size(330, 180);
//    this->labelExplanation->Text = L"Echilibrarea ecua?iilor chimice presupune ajustarea coeficien?ilor astfel încât num?rul de atomi s? fie egal.";
//
//    this->panelExplanation->Controls->Add(this->labelExplanation);
//    this->Controls->Add(this->panelExplanation);
//    this->Controls->Add(this->textBoxEquation);
//    this->Controls->Add(this->buttonSolve);
//    this->Controls->Add(this->labelResult);
//    this->ResumeLayout(false);
//}
//
//// Func?ie pentru parsarea formulelor chimice
//std::map<std::string, int> ReactionSolver::parseFormula(const std::string& formula) {
//    std::map<std::string, int> elementCount;
//    size_t i = 0;
//    while (i < formula.size()) {
//        if (isupper(formula[i])) {
//            std::string element(1, formula[i]);
//            if (i + 1 < formula.size() && islower(formula[i + 1])) {
//                element += formula[i + 1];
//                i++;
//            }
//            int count = 0;
//            while (i + 1 < formula.size() && isdigit(formula[i + 1])) {
//                count = count * 10 + (formula[i + 1] - '0');
//                i++;
//            }
//            if (count == 0) count = 1;
//            elementCount[element] += count;
//        }
//        i++;
//    }
//    return elementCount;
//}
//
//// Func?ie pentru echilibrarea ecua?iei
//void ReactionSolver::buttonSolve_Click(System::Object^ sender, System::EventArgs^ e) {
//    std::string eq = msclr::interop::marshal_as<std::string>(this->textBoxEquation->Text);
//    if (eq.find("->") == std::string::npos) {
//        this->labelResult->Text = L"Ecua?ie invalid?!";
//        return;
//    }
//    // Implementarea echilibr?rii va folosi parseFormula ?i balanceEquation
//}
