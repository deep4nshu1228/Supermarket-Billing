#include <iostream>
#include <process.h>
#include <fstream>
#include <stdlib.h>

class head 
{
    char lname[50][50];
    public:
    int totalitems;
    float Quantity[3];
    float price[3];
    int vatprice[3];
    int tprice[3];
    void input();
    void output();
};

class vat: public head
{
    float vats;
    public:
    void vatcal();
    void outputs();
    void sum();
};

// INPUT FUNCTION

void head:: input()
{
    system("CLS");
    std::cout << "\nEnter Number of Items = ";
    std::cin >> totalitems;

    for(int i=0; i<totalitems; i++){
        std::cout << "\nEnter name of item " << i+1 << ":";
        std::cin >> lname[i];
        std::cout << "Enter Quantity: ";
        std::cin >> Quantity[i];    
        std::cout << "Enter price of item " << i+1 << ":";
        std::cin >> price[i];
        tprice[i] = Quantity[i]*price[i]; 
    }
}

// OUTPUT FUNCTION

void head:: output()
{
    int a;
    std::ifstream infile("COUNT.TXT");
    infile >> a;

    std::ofstream outfile("COUNT.TXT");
    a+=1;
    outfile<<a;

    outfile.close();

    {
        std::ofstream outfile("HIS.TXT", std::ios::app);
        outfile << "\n" << "Bill No. : " << a  << "\n";
        outfile << "__________________________________________________" << "\n";
        std::cout << "\n";
        std::cout << "Name of Item\tQuantity Price Total Price\n";
        for(int i=0; i<totalitems; i++){
            outfile << "Name:" << lname[i] << "Quantity:" << Quantity[i] << "Price:" << tprice[i] << "\n";
            std::cout << lname[i] << "\t\t" << Quantity[i] << "\t" << price[i] << "\t" << tprice[i] << "\n";
        }
        outfile << "__________________________________________________" << "\n";
        outfile.close();
    }
}

// VAT CALCULATION

void vat:: vatcal()
{
    input();
    for(int i=0; i<totalitems; i++)
    {
        if(price[i] <= 100.00)
            vatprice[i] = tprice[i] + (0.03 * tprice[i]);
        else
            vatprice[i] = tprice[i] + (0.1*tprice[i]);
    }
}

// VAT OUTPUTS

void vat:: outputs()
{
    output();

    float cash=0,sum=0,quantity=0,sumt=0;

    for(int i=0; i<totalitems; i++)
    {
        sumt += tprice[i];
        sum += vatprice[i];
        quantity += Quantity[i];
    }
    std::cout << "\nTotal:";
    std::cout << "\n____________________________________________";
    std::cout << "\n\tQuantity = " << quantity << "\t\tSum = " << sumt << "\tWith Vat: " << sum;
    std::cout << "\n____________________________________________";

pay:

    std::cout << "\n\n\t\t\t****Payment Summary****\n";
    std::cout << "\n\t\t\tTotal Cash Given: ";
    std::cin >> cash;

    if(cash >= sum)
        std::cout << "\n\t\t\tTotal cash repaid: " << cash-sum << "\n";
    else{
        std::cout << "\n\t\t\tCash given is less than total amount!!!";
        goto pay;
    }
}

// PROTECTION PASSWORD

int password()
{
    char p1,p2,p3;
    std::cout << "\n\n\n\n\n\n\t\t\tENTER THE PASSWORD: ";

    std::cin >> p1;
    std::cout << "*";
    std::cin >> p2;
    std::cout << "*";
    std::cin >> p3;
    std::cout << "*";

    if( (p1=='s' || p1=='S')&&(p2=='i' || p2=='I')&&(p3=='d' || p3=='D') )
        return 1;
    else
        return 0;   
}


// THE MAIN FUNCTION

int main(){
    vat obj;
    char opt,ch;

    int a=1;
    std::ifstream fin;

    a==password();
    if(!a){
        for(int i=0; i<2; i++){
            std::cout << "\nWrong Password try once more\n";
            if(password()){
                goto last;
            }else{
                std::cout << "\n\n\t\t\tall attempts failed .....";
                std::cout << "\n\n\n\t\tsee you .......";
                exit(0);
            }
        }
        std::cout << "\t\t\tSorry all attempts failed ........ \n\t\t\tinactive";
    }
    else{
        last:;
        do{
            start:
                system("PAUSE");
                system("CLS");
                std::cout << "\n\n\t\t\t -------------------";
                std::cout << "\n\t\t\tBilling Management System";
                std::cout << "\n\t\t\t -------------------";
                std::cout << "\n\n\t\t\tWhat you want to do?";
                std::cout << "\n\t\t\t1.\tTo enter new entry\n\t\t\t2.\tTo view previous entries\n\t\t\t3.\tExit\n";
                std::cout << "\n\nEnter your Option: ";
                std::cin >> opt;
            
            switch(opt){
                case '1':
                    obj.vatcal();
                    obj.outputs();
                    goto start;

                case '2':
                    fin.open("HIS.TXT",std::ios::in);
                    while(fin.get(ch));{
                        std::cout << ch;
                    }
                    fin.close();
                    goto start;

                case '3':
                    exit(0);

                default:
                    std::cout << "\a";
            }
        }while(opt!=3);
    }   
    return 0;
}


