#include <iostream>
#include <string>
#include <algorithm>	//std::find
#include <vector>
#include <unordered_map>

/*
NOTES:
- when using the .find() function for unordered maps, an iterator goes through the list and if it does not find
what it needs to find, then the iterator will reach the end of the unordered map. Otherwise, it will return an
iterator pointing to the found element.
- std::unordered_map::count(key) is a function that searches through the map to find how many times "key" is in the
map. Unordered maps doesn't allow for duplicate keys so it returns 1 if found, and 0 if it doesn't exist.
*/

/*
TO DO:
-Function ID.find(*string*) is sometimes not able to detect if a certain string key is already in the map.
*/

//Function Prototypes
int CheckID(std::string &from_page, std::string &to_page, std::unordered_map<std::string, int> &ID, int IDNum);

void SetupPageRankMatrix(std::vector<std::vector<float>> &pageRankMatrix,
						 std::unordered_map<std::string, int> ID,
						 std::unordered_map<std::string, float> pageOutDegree);

void PowerIteration(std::vector<std::vector<float>> &pageRankMatrix,
					std::vector<float> &powerMatrix,
					std::unordered_map<std::string, float> &pageRank,
					std::unordered_map<std::string, int> &ID,
					int numOfPowerIterations);


int main() {
	std::unordered_map<std::string, int> ID;
	std::unordered_map<std::string, float> pageOutDegree;
	std::unordered_map<std::string, float> pageRank;
	std::vector<std::vector<float>> pageRankMatrix;
	std::vector<float> powerMatrix;
	std::vector<std::string> listOfPages;
	std::string from_page = "";
	std::string to_page = "";
	int numOfLines = 0;
	int numOfPowerIterations = 0;
	int IDNum = 1;

	//std::cout << "Enter number of lines and number of power iterations (separated by a space):" << std::endl;
	std::cin >> numOfLines;
	std::cin >> numOfPowerIterations;

	if (numOfLines == 0) {	//In the case of 0 lines.
		return 0;
	}

	for (int i = 0; i < numOfLines; i++) {
		std::cin >> from_page;
		std::cin >> to_page;
		//std::cout << from_page << "\n" << to_page << "\n";	//(FOR DEBUGGING)
		IDNum = CheckID(from_page, to_page, ID, IDNum);
		if (pageOutDegree.find(from_page) != pageOutDegree.end()) {		//If the page has already occurred at least once
			pageOutDegree[from_page]++;		//Increment its Out Degree value (in this case, pageRank = outDegree)
		}
		else {
			pageOutDegree.insert(make_pair(from_page, 1));
		}

		//std::cout << ID[to_page] << ID[from_page] << " " << pageOutDegree[to_page] << std::endl;		//(FOR DEBUGGING)
		pageRankMatrix.resize(IDNum + 1);
		pageRankMatrix[ID[to_page]].resize(IDNum + 1);

		pageRankMatrix[ID[to_page]][ID[from_page]] = 1.0;

	}

	//Replaces the proper pagerank values
	SetupPageRankMatrix(pageRankMatrix, ID, pageOutDegree);

	//Creates the Power Matrix (the matrix used to multiply page rank matrix at each iteration)
	//Also resizes the pageRankMatrix so it's dimensions equal the number of pages + 1 (Adding 1 is necessary
	//Since the ID Numbers start at "1" while the array indices start at "0".
	powerMatrix.resize(ID.size() + 1);	//Remember that pageRankMatrix has dimensions ID.size() + 1 by ID.size() + 1
	pageRankMatrix.resize(ID.size() + 1);
	for (int i = 0; i < powerMatrix.size(); i++) {
		powerMatrix[i] = 1.0 / ID.size();
		pageRankMatrix[i].resize(ID.size() + 1);
	}

	for (auto x : ID) {
		pageRank.insert(make_pair(x.first, (float)(1.0 / ID.size())));
	}

	//Power Iterations
	PowerIteration(pageRankMatrix, powerMatrix, pageRank, ID, --numOfPowerIterations);

	for (auto x : ID) {
		listOfPages.push_back(x.first);
	}
	std::sort(listOfPages.begin(), listOfPages.end());

	for (auto x : listOfPages) {
		float value = (int)(pageRank[x] * 100 + .5);	//Rounding algorithm: https://www.geeksforgeeks.org/rounding-floating-point-number-two-decimal-places-c-c/
		pageRank[x] = (float)value / 100;
		std::cout << x;
		printf(" %1.2f\n", pageRank[x]);
	}
	
	/*
		//SECTION AFTER THIS IS FOR DEBUGGING PURPOSES
	

	std::cout << "\n\n\n******DEBUGGING******\n\n\n";

	//Prints the ID and the Out Degree of each page (FOR DEBUGGING)
	for (auto x : ID) {	
		std::cout << x.first << " ID: " << x.second << "; Out Degree: " << pageOutDegree[x.first] << std::endl;
	}

	std::cout << "Matrix size: " << pageRankMatrix.size() << std::endl;		//(FOR DEBUGGING)

	//Prints the Page Rank Matrix (FOR DEBUGGING)
	for (int i = 0; i < pageRankMatrix.size(); i++) {			
		for (int j = 0; j < pageRankMatrix[i].size(); j++) {
			std::cout << pageRankMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}

	//Prints the power Matrix (FOR DEBUGGING)
	for (auto x : powerMatrix) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	//Prints the final page ranks for each page after all power iterations (FOR DEBUGGING)
	for (auto x : pageRank) {
		std::cout << x.first << " " << x.second << std::endl;
	}
	std::cout << std::endl;
	system("pause");*/
	return 0;
}

int CheckID(std::string &from_page, std::string &to_page, std::unordered_map<std::string, int> &ID, int IDNum) {
	if (ID.count(from_page) == 0) {	//from_page does not have a unique ID
		ID.insert(make_pair(from_page, IDNum));
		IDNum++;
		//std::cout << "Made ID for " << from_page << std::endl;		//(FOR DEBUGGING)
	}
	if (ID.count(to_page) == 0) {	//to_page does not have a unique ID
		ID.insert(make_pair(to_page, IDNum));
		IDNum++;
		//std::cout << "Made ID for " << to_page << std::endl;		//(FOR DEBUGGING)
	}
	return IDNum;
}

void SetupPageRankMatrix(std::vector<std::vector<float>> &pageRankMatrix,
						 std::unordered_map<std::string, int> ID,
						 std::unordered_map<std::string, float> pageOutDegree) {

	for (int i = 0; i <= ID.size(); i++) {
		for (int j = 0; j < pageRankMatrix[i].size(); j++) {
			if (pageRankMatrix[i][j] != 0) {
				for (auto x : ID) {
					//std::cout << x.second << j << ID.size() << std::endl;		//(FOR DEBUGGING)
					if (x.second == j) {
						//std::cout << "ENTER" << std::endl;		//(FOR DEBUGGING)
						pageRankMatrix[i][j] = 1.0 / pageOutDegree[x.first];
					}
				}
			}
		}
	}
}

void PowerIteration(std::vector<std::vector<float>> &pageRankMatrix,
					std::vector<float> &powerMatrix,
					std::unordered_map<std::string, float> &pageRank,
					std::unordered_map<std::string, int> &ID,
					int numOfPowerIterations) {

	float newPageRank = 0.0;
	for (int i = numOfPowerIterations; i > 0; i--) {
		for (int j = 0; j < pageRankMatrix.size(); j++) {
			newPageRank = 0.0;
			for (int k = 0; k < pageRankMatrix.size(); k++) {
				if (pageRankMatrix[j][k] == 0) { continue; }
				newPageRank += (pageRankMatrix[j][k] * powerMatrix[k]);
			}
			//std::cout << newPageRank << std::endl;		//(FOR DEBUGGING)
			for (auto x : ID) {
				if (x.second == j) {
					pageRank[x.first] = newPageRank;
				}
			}
		}

		//Update power matrix
		for (auto x : ID) {
			powerMatrix[x.second] = pageRank[x.first];
		}
	}

}