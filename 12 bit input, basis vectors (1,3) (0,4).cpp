#include<iostream>
#include<bitset>
#include <string>
#include <math.h>
#include<sstream>

using namespace std;

int input_size = 12;
int x = 1;
int y = 3;
int z = 4;

int verticalsymmetry(int* p[1]) // draw a vertical line cutting the 2d array into 2 parts and return 1 if the 2 parts are symmetric
{
    if (x<2) return 0;
    else {
        for (int i=0; i<z; i++)
        {
            for (int j=0; j<(x/2); j++)
            {
                if ((p[i][j]!= p[i][j+(x/2)]))
                    return 0;
            }
        }
        return 1;
    }
}

//draw a horz line thru the 2d array and divide it into two, and check if they are symmetric
int horizontalsymmetry(int* p[1])
{
    if (z<2) return 0;
    else {
        for (int j=0; j<x; j++)
        {
            for (int i=0; i<(z/2); i++)
            {
                if ((p[i][j]!= p[i+(z/2)][j]))
                    return 0;
            }
        }
        return 1;
    }
}

//divide the array into 4 by drawing 1 vertical and 1 horizontal line and check if the opposite parts are the same
int diagonalsymmetry(int* p[1])
{
    if ((z<2) || (x<2)) return 0;
    else {
        for (int j=0; j<x/2; j++)
        {
            for (int i=0; i<z/2; i++)
            {
                if ((p[i][j]!=p[i+(z/2)][j+(x/2)]) || (p[i+(z/2)][j]!=p[i][j+(x/2)]))
                    return 0;
            }
        }
        return 1;
    }
}

//if even one of the three symmetries exist, this will return 1
int checksymmetry(int* p[1])
{
    int sum = verticalsymmetry(p) + horizontalsymmetry(p) + diagonalsymmetry(p);
    if (sum>0) return 1;
    else return 0;
}

//takes all 3 planes as input and prints the state as 3 planes all represented as binary
void printstatebinary(int* planea[1], int* planeb[1], int* planec[1])
{
    for(int i=0;i<z;i++)
    {
        for(int j=0;j<x;j++)
        {
            cout<<planea[i][j]<<" ";
        }cout<<endl;
    }cout<<endl;
    for(int i=0;i<z;i++)
    {
        for(int j=0;j<x;j++)
        {
            cout<<planeb[i][j]<<" ";
        }cout<<endl;
    }cout<<endl;
    for(int i=0;i<z;i++)
    {
        for(int j=0;j<x;j++)
        {
            cout<<planec[i][j]<<" ";
        }cout<<endl;
    }cout<<endl;
    cout<<endl;
}

//prints the state that is a decimal representation of the three binary planes
void printstatedecimal(int* out[1])
{
    for(int i=0;i<z;i++)
    {
        for(int j=0;j<x;j++)
        {
            cout<<out[i][j]<<" ";
        }cout<<endl;
    }cout<<endl;
}

//converts the decimal value q to a 24 bit binary and inserts it into the three planes in order
void insertintostate(int q, int* planea[1], int* planeb[1], int* planec[1])
{
    int *bin = new int[input_size];
    for(int i=0; i<input_size; i++) { bin[i]=0; }
    int c=0;
    for (int i = input_size-1; i >= 0; i--)
    {
        int k = q >> i;
        if (k & 1) bin[c] = 1;
        else bin[c] = 0;
        c++;
    }
    c = 0;
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            planea[i][j] = bin[c];
            c++;
        }
    }
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            planeb[i][j] = bin[c];
            c++;
        }
    }
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            planec[i][j] = bin[c];
            c++;
        }
    }
}

long binarytodecimal(string bits)
{
    if(bits != "")
    {
        int decimal = 0;
        for(int i = (bits.length() - 1), j = 0; i >=0 && j<bits.length(); i--, j++)
        {
            switch(bits.at(j))
            {
                case '1':
                    decimal += pow(2, i);
                    break;
                case '0':
                    break;
                default:
                    decimal = -1;
                    break;
            }
            if(decimal == -1)break;
        }
        return decimal;
    }
    return -1;
}

//concatenate the values of planea[i][j], planeb[i][j], planec[i][j] and convert it into a decimal
void planetostate(int* planea[1], int* planeb[1], int* planec[1], int* out[1])
{
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            string s = "";
            std::stringstream s1;
            s1 << planea[i][j];
            s += s1.str();
            std::stringstream s2;
            s2 << planeb[i][j];
            s += s2.str();
            std::stringstream s3;
            s3 << planec[i][j];
            s += s3.str();
            out[i][j] = (int)binarytodecimal(s);
            
        }
    }
}

//converts the entire state to a string of binary bits
string statetobinary(int* planea[1], int* planeb[1], int* planec[1])
{
    string s = "";
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            std::stringstream ss;
            ss << planea[i][j];
            s += ss.str();
        }
    }
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            std::stringstream ss;
            ss << planeb[i][j];
            s += ss.str();
        }
    }
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            std::stringstream ss;
            ss << planec[i][j];
            s += ss.str();
        }
    }
    return s;
}

//cyclic rotation of each plane by one position
void singlepositionshift(int* planea[1], int* planeb[1], int* planec[1])
{
    int q=0;
    int *a = new int[x*z];
    int *b = new int[x*z];
    int *c = new int[x*z];
    
    for (int i=0; i<z; i++)
    {
        for(int j=0; j<x; j++)
        {
            a[q] = planea[i][j];
            b[q] = planeb[i][j];
            c[q] = planec[i][j];
            q++;
        }
    }
    q = x*z;
    for (int i=0; i<z; i++)
    {
        for(int j=0; j<x; j++)
        {
            int k = (q-1)%(x*z);
            planea[i][j] = a[k];
            planeb[i][j] = b[k];
            planec[i][j] = c[k];
            q++;
        }
    }
}


//check if the 2 planes are equal
int checkplane(int* planea[1], int* planeb[1])
{
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            if (planea[i][j] != planeb[i][j])
                return 0;
        }
    }
    return 1;
}


//values of planea are put into temp
void equateplane(int* planea[1], int* temp[1])
{
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            temp[i][j] = planea[i][j];
        }
    }
}

//shifts planea by values xshift and zshift and inserts the resutl into temp
void shiftplane(int xshift, int zshift, int* planea[1], int* temp[1])
{
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            temp[(i+(zshift%z))%z][(j+(xshift%x))%x] = planea[i][j];
        }
    }
}

void xorplane(int* planea[1], int* planeb[1], int* temp[1])
{
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            temp[i][j] = (planea[i][j] == planeb[i][j]) ? 0 : 1;
        }
    }
    
}

void complimentplane(int* planea[1], int* temp[1])
{
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            temp[i][j] = (planea[i][j] == 1) ? 0 : 1;
        }
    }
}

void andplane(int* planea[1], int* planeb[1], int* temp[1])
{
    for (int i=0; i<z; i++)
    {
        for (int j=0; j<x; j++)
        {
            temp[i][j] = (planea[i][j] + planeb[i][j] == 2) ? 1 : 0;
        }
    }
}
void mixinglayer(int* planea[1], int* planeb[1], int* planec[1], int* temp[1])
{
    
    int** P = new int*[z];
    int** E = new int*[z];
    for(int i=0;i<z;i++)
    {
        P[i] = new int[x];
        E[i] = new int[x];
    }
    
    xorplane(planea,planeb,temp);
    xorplane(temp,planec,P);//P now contains xor of all 3 planes.
    
    equateplane(P,E); //E now has the values of P
    shiftplane(0,2,P,temp); //shifts P, state_parsed in temp
    shiftplane(0,3,E,P);//shifts E, puts new value into P
    xorplane(P,temp,E); //xor of P and temp is now in value 'E'
    
    xorplane(planea,E,planea);
    xorplane(planeb,E,planeb);
    xorplane(planec,E,planec);
}

void rhowest(int* planea[1], int* planeb[1], int* planec[1], int* temp[1])
{
    shiftplane(0,1,planeb,temp);
    equateplane(temp,planeb);
    
    shiftplane(0,3,planec,temp);
    equateplane(temp,planec);
}

void rhoeast(int* planea[1], int* planeb[1], int* planec[1], int* temp[1])
{
    //cout<<"rhoeast"<<endl;
    //printstatebinary(planea,planeb,planec);
    shiftplane(0,1,planeb,temp);
    equateplane(temp,planeb);
    
    shiftplane(0,2,planec,temp);
    equateplane(temp,planec);
    //printstatebinary(planea,planeb,planec);
}

void nonlinearlayer(int* planea[1], int* planeb[1], int* planec[1], int* temp[1])
{
    //cout<<"non linear: "<<endl;
    //printstatebinary(planea,planeb,planec);
    
    int** B = new int*[z];
    int** tempA = new int*[z];
    int** tempC = new int*[z];
    for(int i=0;i<z;i++)
    {
        B[i] = new int[x];
        tempA[i] = new int[x];
        tempC[i] = new int[x];
    }
    
    complimentplane(planea,temp);
    andplane(temp,planeb,B);
    
    xorplane(planec,B,tempC);
    
    complimentplane(planeb,temp);
    andplane(temp,planec,B);
    
    xorplane(planea,B,tempA);
    
    complimentplane(planec,temp);
    andplane(temp,planea,B);
    
    xorplane(planeb,B,planeb);
    
    equateplane(tempC,planec);
    equateplane(tempA,planea);
    
    //printstatebinary(planea,planeb,planec);
}

void roundfunction(int* planea[1], int* planeb[1], int* planec[1], int* temp[1])
{
    mixinglayer(planea,planeb,planec,temp);
    rhowest(planea,planeb,planec,temp);
    nonlinearlayer(planea,planeb,planec,temp);
    rhoeast(planea,planeb,planec,temp);
}

//used to check if array c is indeed a shifted/rotated version of array o
int arraycyclecheck(int shift,int *o,int *c)
{
    for(int i=0; i<(x*z); i++)
    {
        if (c[i] != o[(i+shift)%(x*z)])
            return 0;
    }
    return 1;
}

//check if array 'check' is a cyclic/shifted version of array 'out'
int statecyclecheck(int* out[1], int* check[1])
{
    int *o = new int[x*z];
    int *c = new int[x*z];
    int q = 0;
    for (int i=0; i<z; i++)
    {
        for (int j=0;j<x; j++)
        {
            o[q] = out[i][j];
            c[q] = check[i][j];
            q++;
        }
    }
    int sum = 0;
    for (int i=1; i<q; i++)
        sum += arraycyclecheck(i,o,c);
    
    if (sum == 1) return 1;
    else return 0;
}

void shiftcheck(int xshift, int zshift, int* planea[1], int* planeb[1], int* planec[1], int* newplanea[1], int* newplaneb[1], int* newplanec[1])
{
    shiftplane(xshift,zshift,planea, newplanea);
    shiftplane(xshift,zshift,planeb, newplaneb);
    shiftplane(xshift,zshift,planec, newplanec);
}

int whileconditioncheck(int* planea[1], int* newplanea[1])
{
    int** extra = new int* [z];
    for (int i=0; i<z; i++)
        extra[i] = new int[x];
    
    for (int shift = 0; shift < z; shift++)
    {
        shiftplane(0,shift,planea,extra);
        if (checkplane(newplanea, extra)) return shift;
    }
    return -1;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


int main()
{
    
    cout<<"Input size: "<<input_size<<" bits."<<endl;
    cout<<"Xoodoo state coordinates: x = "<<x<<", y = 3, z = "<<z<<endl;
    cout<<"Mixing layer equation: E <- P <<< ("<<(1 % x)<<", "<<(5 % z)<<") + P <<< ("<<(1 % x)<<", "<<(14 % z)<<")"<<endl;
    cout<<"Rho west equation: A1 <<< ("<<(1 % x)<<", 0) and A2 <<< (0, "<<(11 % z)<<")"<<endl;
    cout<<"Rho east equation: A1 <<< (0, "<<(1 % z)<<") and A2 <<< ("<<(2 % x)<<", "<<(8 % z)<<")"<<endl<<endl;
    
    //create 3 dynamic 2d arrays(each being one plane, the three planes put together to form a state), a state to represent the decimal notation of the three 2d arrays when looking at it from the top, temp and check are for calculations later
    int** planea = new int*[z];
    int** planeb = new int*[z];
    int** planec = new int*[z];
    int** newplanea = new int*[z];
    int** newplaneb = new int*[z];
    int** newplanec = new int*[z];
    int** state = new int*[z];
    int** temp = new int*[z];
    int** check = new int*[z];
    for(int i=0;i<z;i++)
    {
        planea[i] = new int[x];
        planeb[i] = new int[x];
        planec[i] = new int[x];
        newplanea[i] = new int[x];
        newplaneb[i] = new int[x];
        newplanec[i] = new int[x];
        state[i] = new int[x];
        temp[i] = new int[x];
        check[i] = new int[x];
    }
    
    
    
    //2^24 inputs as 24 is the input size
    int total_inputs = 1;
    for (int i=0; i<input_size; i++)
        total_inputs*=2;
    
    //to check which of the 2^24 states have been parsed during a cycle. it is initialized to 0, and if parsed, it's marked as 1
    int* parsed = new int[total_inputs];
    for (int i=0; i<total_inputs; i++)
        parsed[i] = 0;
    
    int **cyclearray = new int*[10];
    for (int i=0; i<10; i++)
        cyclearray[i] = new int[2];
    for (int i=0;i<10;i++)
    {
        cyclearray[i][0]=0;
        cyclearray[i][1]=0;
        
    }
    
    int cycles = 0;
    int offset = -1;
    //the main loop of the program
    for (int q=0; q<total_inputs; q++)
    {
        //insert the decimal value 'q' into the 3 planes in binary
        insertintostate(q,planea,planeb,planec);
        
        //convert the 3 binary planes into a state which is in the form of a decimal plane
        planetostate(planea, planeb, planec, state);
        
        //check if has already been parsed or if the state has a symmetrical structure - if so continue with the loop.
        if (parsed[q]!=0 || (checksymmetry(state)==1))  continue;
        else
        {
            //cout<<q<<" entered else loop."<<endl;
            cout<<"Input in decimal: "<<q<<endl;
            printstatedecimal(state);
            int count = 0; //to count number of states that are parsed before a cycle is found
            
            do
            {
                for (int shift = 0; shift < z; shift++)
                {
                    shiftcheck(0,shift,planea,planeb,planec,newplanea,newplaneb,newplanec);
                    parsed[binarytodecimal(statetobinary(newplanea,newplaneb,newplanec))] = 1;
                }
                
                //perform the round function on the state
                roundfunction(planea, planeb, planec, temp);
                planetostate(planea, planeb, planec, check);
                count++;
                offset = whileconditioncheck(state,check);
            } while(offset<0);
            
            cyclearray[cycles][0] = count;
            if (offset==0) cyclearray[cycles][1] = 2;
            else cyclearray[cycles][1] = 1;
            cycles+=1;
            
        }
    }
    
    int i,j;
    for (i = 0; i < cycles-1; i++)
    {
        // Last i elements are already in place
        for (j = 0; j < cycles-i-1; j++)
            if (cyclearray[j][0] < cyclearray[j+1][0])
            {
                swap(&cyclearray[j][0], &cyclearray[j+1][0]);
                swap(&cyclearray[j][1], &cyclearray[j+1][1]);
            }
    }
    
    int total = 0;
    
    cout<<"CYCLE RESULTS: "<<endl<<endl;
    for (int i=0; i<cycles; i++)
    {
        cout<<"Supercycle length: "<<cyclearray[i][0]<<", number of cycles: "<<cyclearray[i][1]<<endl;
        total+=cyclearray[i][1];
    }
    cout<<endl<<"Total number of cycles: "<<total<<endl<<endl;
    
    
    return 0;
}
