// traveling.cpp
// Asadbek Shamsiev, as9vd
// November 30th, 2021

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>

using namespace std;

#include "middleearth.h"

float computeDistance(MiddleEarth& me, const string& start, vector<string>& dests);
void printRoute(const string& start, const vector<string>& dests);

/* \author Asadbek Shamsiev 
*/

/* \fn int main(int argc, char** argv)
*/ 
int main(int argc, char** argv) {
    // check the number of parameters

    if (argc != 6) {
        cout << "Usage: " << argv[0] << " <world_height> <world_width> "
             << "<num_cities> <random_seed> <cities_to_visit>" << endl;
        exit(0);
    }

    // we'll assume the parameters are all well-formed
    int width = stoi(argv[1]);
    int height = stoi(argv[2]);
    int num_cities = stoi(argv[3]);
    int rand_seed = stoi(argv[4]);
    int cities_to_visit = stoi(argv[5]);

    // create the world, and select your itinerary
    MiddleEarth me(width, height, num_cities, rand_seed);
    vector<string> dests = me.getItinerary(cities_to_visit);

    // -----------------------------------------------------------------

    const string start = dests.front();
    dests.erase(dests.begin());

    vector<vector<string>> permutations;
    vector<float> distances;

    sort(dests.begin(), dests.end());

    do {
        float distance = computeDistance(me, start, dests);

        permutations.push_back(dests);
        distances.push_back(distance);

    } while (next_permutation(dests.begin(), dests.end())); // A glorified iterator.

    double temp = 100.00;
    int index = 0;

    for (int i = 0; i < distances.size(); i++) { // Returns the min distance and the index of the min distance.
        if (distances[i] < temp) {
            temp = distances[i]; 
            index = i;
        }
    }

    cout << "Minimum path has distance " + to_string(temp) + ": ";
    printRoute(start, permutations[index]);

    return 0;
}

// This method will compute the full distance of the cycle that starts
// at the 'start' parameter, goes to each of the cities in the dests
// vector IN ORDER, and ends back at the 'start' parameter.

// Need:
// 1. Distance from start to [0]
// 2. Normal distances in the vector
// 3. Distance from [last] to start
float computeDistance(MiddleEarth& me, const string& start, vector<string>& dests) {
    float sum = 0;

    sum += me.getDistance(start, dests[0]); // 1.

    for (int i = 1; i < dests.size(); i++) { // 2. 
        sum += me.getDistance(dests[i - 1], dests[i]);

        if (i == dests.size() - 1) {
            sum += me.getDistance(dests[i], start); // 3.
        }
    }

    if (dests.size() == 1) {
        sum += me.getDistance(dests[0], start);
    }

    return sum - 0.00001;
}

// This method will print the entire route, starting and ending at the
// 'start' parameter.
// The output should be similar to:
// Erebor -> Khazad-dum -> Michel Delving -> Bree -> Cirith Ungol -> Erebor
void printRoute(const string& start, const vector<string>& dests) {
    cout << start + " -> ";

    for (int i = 0; i < dests.size(); i++) {
        if (i == dests.size() - 1) {
            cout << dests[i] + " -> " + start << endl;
            break;
        }

        cout << dests[i] + " -> ";
    }
}