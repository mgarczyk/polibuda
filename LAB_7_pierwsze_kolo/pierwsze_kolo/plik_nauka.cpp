#include <iostream>
#include <algorithm>

using namespace std;
void maksimum_ile(int tab_maxi[][2], const int wiersze, const int kolumny){
    
                int maximum = tab_maxi[0][0];
                for(int i=0;i<wiersze;i++){
                    for(int j=0;j<kolumny;j++){
                        if(tab_maxi[i][j] > maximum) maximum = tab_maxi[i][j];
                }
                }
                 int licznik = 0;
                 for(int i=0;i<wiersze;i++){
                    for(int j=0;j<kolumny;j++){
                        if(tab_maxi[i][j] == maximum) licznik++;
                    }
                }
                cout<<maximum<<" "<<licznik;
}

int licznik_wzorzec(string tekst, string wzorzec){
                int licznik = 0;
                bool wzorzec_wystapil = true;
                for(int i=0;i<tekst.length()-wzorzec.length() + 1;i++){
                    for(int j=0;j<wzorzec.length();j++){
                        if(tekst[i + j] != wzorzec[j]) wzorzec_wystapil = false;
                    }
                    if(wzorzec_wystapil == true) licznik++;
                    wzorzec_wystapil = true;
                }
                return licznik;
}

bool czy_rowne (int tab_1[2], int tab_2[2], const int rozmiar){
    
                sort(tab_1, tab_1+rozmiar); //sortowanie 1
                sort(tab_2, tab_2+rozmiar); //sortowanie 2
                bool rowne = true;
                for(int i=0; i<rozmiar; i++){
                    if(tab_1[i] != tab_2[i]) return false;
                }
                return true;
                
}
void przedzial (double tab[3], const int rozmiar, double a, double b){
    
                for(int i=0;i<rozmiar;i++){
                        do{
                            cin>>tab[i];
                        }while(tab[i]<a or tab[i]>b);                    
                }
                cout<<"Resulting array:";
                for(int i=0;i<rozmiar;i++){
                    cout << tab[i] << " ";
                }
}
int main(){
    int info;
    cin>>info;
    
    if(info==1 or info==2 or info==3 or info==4){
        switch(info){
            case 1: {
                int tab_maxi[2][2];
                const int wiersze = 2;
                const int kolumny = 2;
                for(int i=0;i<wiersze;i++){
                    for(int j=0;j<kolumny;j++){
                        cin>>tab_maxi[i][j];
                    }
                }
               maksimum_ile(tab_maxi, wiersze, kolumny);
                
                break;
            }
            case 2: {
                string tekst, wzorzec;
                cin>>tekst>>wzorzec;
                int licznik  = licznik_wzorzec(tekst, wzorzec);
                cout<<licznik;
                break;
            }
            case 3: {
                const int rozmiar = 2;
                int tab_1[2], tab_2[2];
                
                for(int i=0;i<rozmiar;i++){
                    cin>>tab_1[i];
                    tab_2[i] = (int)tab_1[i]; 
                }
                
                 for(int i=0;i<rozmiar;i++){
                    cin>>tab_2[i];
                    tab_2[i] = (int)tab_2[i];                
                     
                 }
                 bool rowne = czy_rowne(tab_1, tab_2, rozmiar);
                 if(rowne == true) cout<<"Equal.";
                 else{
                     cout<<"Different";
                 }
                break;
            }
            case 4: {
                
                double a, b;
                cin>>a>>b;
                double tab[3];
                const int rozmiar = 3;
                przedzial(tab, rozmiar, a, b);
                break;
            }
        }
        
    }else{
        cout<<"Wrong task number";
    }
}
