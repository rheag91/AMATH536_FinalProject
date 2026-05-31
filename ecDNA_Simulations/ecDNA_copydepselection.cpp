

#include "Anfangsverteilung.h"

#include <random>



# include <iostream>
# include <cmath>
# include <ctime>
# include <cstdlib>
# include <cstdio>
# include <vector>
# include <fstream>
#include <math.h>
#include <algorithm>  

using std::vector;
using std::cout;
using std::cin;



int NumCells = 1000;    // Maximum number of cells

int NumNeutral = 0;      // Initial number of cells with no ecDNA

int amplify = 2;         // factor of ecDNA amplification upon cell division X -> amplify * X


double fitness[500];      // relative fitness of cells with ecDNA ( fitness =1 corresponds to neutral dynamics)

int initialcopies = 100; // Initial copies of ecDNA in the first founder cell

int runs = 1;         // Number of simulation repeats


// Initiate a bunch of vectors to store cell states troughout the simulation

vector <double> State (1,initialcopies); //stores ecDNA copy number of each cell (one cell per entry, number of ecDNA copies is the entry)

vector < vector <double> > FinalOutput (runs ,vector <double> (NumCells+1,0));

vector < vector <double> > Neutral (runs ,vector <double> (NumCells,0));

vector <double> Rate (NumCells ,0); 

vector <double> Rate1 (NumCells ,0);


// Initiate random number generator

time_t seconds ;
// MTRand mtrand1(time(NULL));

std::random_device rd;
std::mt19937 gen(rd());


// Define a function to generate a random number for the Gillespie Algorithm (Defined at the bottom)

double exprand( double lambda );





int main()
{
    
    int count1 = 0;  // Dummy variable to count number of simulation repeats

    // initialize fitness array
    for (int i=0; i<100; i++)
    {
        fitness[i] = 1.0 + 0.01*i;
    }
    for (int i=100; i<500; i++)
    {
        fitness[i] = 2.0;
    }
    
    while (count1 < runs)
    {
       
        int count = 0; // Dummy Variable to count until the number of maximal cells
        int cell_copy_counts[500] = {0}; 
        cell_copy_counts[initialcopies] = 1; //indicates 1 cell in the initialcopies state
        
        // Reset some of the vectors of the simulation
        
        State.resize(1);
        State.at(0)=initialcopies;
        NumNeutral = 0; //count cells with no ecDNA
        
        
        while (count < NumCells)
        {
            cout << count1 << " " << count << "\n"; // output current state of the simulation
            
            // Define a bunch of dummy variables to store intermediate ecDNA copy number and cell fitness
            
            double a1 = 0;
            double a2 = 0;
            double a3 = 0;
            
            double s1 = 0;
            double s2 = 0;
            double s3 = 0;
            
            // Run the Gillespie algorithm to decide which cell should divide next (here it is only 2 possible divisions, cells with or without ecDNA
            // The Gillespie algorithm can be more complicated and can contain cell death negative selection or copy number dependent selection etc.
            
            a1 = exprand( NumNeutral ); // Random number of neutral cell population
            a2 = fitness * State.size(); // ecDNA cell population with adjusted rate
            a3 = exprand( a2 );         // Random number of ecDNA cell population
            
            Neutral.at(count1).at(count) = NumNeutral ; //indexes Neutral to store the number of neutral cells 
            
            // If a1 < a3 a neutral cell is picked for proliferation. In contrast if a3 >= a1 a cell with ecDNA is picked for proliferation
            
            if (a1 <= a3)
            {
                NumNeutral++;
                    
            }
            else
            {
                
                if (State.size() > 0)
                {  std::uniform_int_distribution<> dist(0, State.size() - 1);
                    s1 = dist(gen); // Pick a random cell with ecDNA to proliferate
                    
                    double c4 = amplify*State.at(s1);  // double the ecDNA copies in the mother cell
                    
                    
                    std::binomial_distribution<> d(c4 ,0.5); // Random binomial trail to distribute the ecDNA copies into daughter cells
                    
                    s2 = d(gen); //draw the number of ecDNA copies in one of the daughter cells
                    
                    // Below is just a few statements to make sure to count all possible cases of daughter cells correctly
                    
                    if (s2==2) 

                    {Rate1.at(count)++;}

                    s3 = State.at(s1);
                }
                else 
                {
                    s1 = 0;
                    
                   double c4 = amplify*State.at(s1);
                    
                    
                    std::binomial_distribution<> d(c4 ,0.5);
                    
                    s2 = d(gen);
                    
                    if (s2==2)
                    {Rate1.at(count)++;}

                    
                    s3 = State.at(s1);
                }
                
                
                if (s2==0)
                {
                    NumNeutral++;
                    State.at(s1) = amplify*s3;
                    Rate.at(count)++ ;
                    
                }
                else
                { State.at(s1)=s2;
                    
                    if ((amplify*s3) == s2)
                    {NumNeutral++;
                     Rate.at(count)++ ;
                    }
                    else
                    {
                        double c3 = (amplify*s3) - s2;
                        
                      
                        
                        State.push_back(c3); //adding a new cell with the remaining ecDNA copies
                        
                        
                    }
                    
                }
                
                
            }
            
            
            count++;
            
        }
        
        
        for (int i=0; i<State.size(); i++)
        {
            FinalOutput.at(count1).at(i)= State.at(i);
            
        }
        
        
        for (int i=State.size(); i<(NumCells); i++)
        {
            FinalOutput.at(count1).at(i)= 0;
            
        }
        
        
        
        count1++;
    }
    
    
    
    std::fstream datei ;
   /*datei.open ("NonNeutral().txt" ,std::ios::out);
    for ( int i=0 ; i < State.size() ; i++)
    {		datei << State.at(i) << " " ;}
    datei.close() ;*/
    
    /*datei.open ("Rate.txt" ,std::ios::out);
    for ( int i=0 ; i < NumCells ; i++)
    {		datei << Rate.at(i) << "\n " ;}
    datei.close() ;*/
    
   /* datei.open ("Rate1.txt" ,std::ios::out);
    for ( int i=0 ; i < NumCells ; i++)
    {		datei << Rate1.at(i) << "\n " ;}
    datei.close() ;*/

    
    /*datei.open ("Neutral2.txt" ,std::ios::out);
    for ( int i=0 ; i<runs ; i++)
    { if (i!=0)
    { datei << "\n" ;}
        for ( int j=0 ; j< NumCells ; j++)
            datei << Neutral.at(i).at(j) << " " ;}
    datei.close() ;*/
    
    
    // This gives the ecDNA copy number for each cell at the end of the simulation (all measures can be constructed from here)
    // need to save neutral cells!
    datei.open ("NonNeutralSummaryPC3.txt" ,std::ios::out);
    for ( int i=0 ; i<runs ; i++)
    { if (i!=0)
    { datei << "\n" ;}
        for ( int j=0 ; j< NumCells ; j++)
            datei << FinalOutput.at(i).at(j) << " " ;}
    datei.close() ;
   
    
}     

double exprand( double lambda)
{
    std::uniform_real_distribution<> unif(0.0, 1.0);
    double y = unif(gen);
    return (-log(1.-y)/lambda); // transform uniform distribution to exponential distribution with rate lambda
}








