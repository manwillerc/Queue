//proj3.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Queue.h"

using namespace std;

int main() {

   //=======read in matrix and store values========
    ifstream fin("proj3.input");

    //reads in number of cities from file and outputs
    int numCities;
    fin >> numCities;
    fin >> ws;
    cout << "Number of cities: " << numCities << endl;

    //creates vector of city names and makes space for the amount of cities
    vector<string> cities;
    cities.reserve(numCities);

    //reads in names of cities and stores in cities vector
    fin >> ws;
    for(int i = 0; i < numCities; i++) {
        string name;
        getline(fin, name);
        cities.push_back(name);
    }

    //outputs city names
    cout << "Cities loaded:\n";
    for(int i = 0; i < numCities; i++) {
        cout << " [" << i << "] " << cities[i] << "\n";
    }

    //creates matrix for prices and fills using values in file
    vector<vector<int> > price(numCities, vector<int>(numCities));

    for(int i = 0; i < numCities; i++) {
        for (int k = 0; k < numCities; k++) {
            fin >> price[i][k];
        }
    }

    //outputs price matrix
    cout << "prices:\n";
    for (int i = 0; i < numCities; i++) {
        for(int k = 0; k < numCities; k++) {
            cout << price[i][k] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //creates a map to store an index value for each city and outputs
    unordered_map<string, int> cityIndex;

    for(int i = 0; i < numCities; i++) {
        cityIndex[cities[i]] = i;
    }
    cout << "pairs:\n";
    for(auto &p : cityIndex) {
        cout << " " << p.first << " " << p.second << endl;
    }

    //=========user input and store values=========
    string source;
    string destination;

    //prompts user for source and destination cities and checks for error
    cout << "\nEnter source city: ";
    getline(cin >> ws, source);
 
    cout << "Enter destination city: ";
    getline(cin >> ws, destination);

    if(cityIndex.find(source) == cityIndex.end()) {
        cout << "Error: source city not found.\n";
        return 1;
    }

    if(cityIndex.find(destination) == cityIndex.end()) {
        cout << "Error: destination city not found.\n";
        return 1;
    }

    cout << "\nsearching from: " << source << " to " << destination << endl;


    //===========create queue to track path============
    cop4530::Queue<int> q;
    vector<bool> visited(numCities, false);
    vector<int> parent(numCities, -1);

    //creates a start variable that holds the index of starting city and goal variable that holds idex of destination city
    int start = cityIndex[source]; 
    int goal = cityIndex[destination];

    //adds start city to queue and sets visited for start city to true
    q.push(start); 
    visited[start] = true; 

    //==========BFS===========
    bool found = false;
    while (q.empty() == false) {        //while there are cities in the queue keep looping
        int current = q.front();        //set current city location to the city at front of queue
        q.pop();                        //remove city from queue while there

        if(current == goal) {           //if the current city is the destination city, end loop
            found = true;
            break;
        }

        for(int i = 0; i < numCities; i++) {                        //for every possible destination, check for direct flight and if it has been visited
            if(price[current][i] > 0 && visited[i] == false) {
                visited[i] = true;
                parent[i] = current;                                //if the current city has a flight to the next it is the parent
                q.push(i);                                          //if conditions are true add city to back of queue
            }
        }
    }

    //===========Handle BFS result============
    //check if route was found or not
    if (found == false) {                              
        cout << "No route found.\n";
        return 0;
    }

    //route found confirmation output
    cout << "Route found. Reconstructing...\n";

    //=========form route using parents======
    //create path that holds city path from goal to start
    vector<int> path;
    for(int city = goal; city != -1; city = parent[city]) {
        path.push_back(city);
    }

    //flip path so that it is from start to finish
    reverse(path.begin(), path.end());

    //output the path
    cout << "\nShortest route by number of connections:\n";
    for(int i = 0; i < path.size(); i++) {
        cout << cities[path[i]];
        if(i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;



    return 0;

}
