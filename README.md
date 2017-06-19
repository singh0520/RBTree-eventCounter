# RBTree-eventCounter
This project demonstrates an event-counter using a Red-Black Tree written in C++. The code takes in input from stdin and prints to stdout. The list of functions it can perform are:

void Increase (int theID, int m): This function increases the value of theID by m. It searches for the node whose data is theID and once it’s found, it increases it’s counter by m. If theID is not present, it inserts theID into the Red Black Tree. The complexity is O(log n).

void Reduce (int theID, int m): This function decreases the value of theID by m. It searches for the node whose data is theID and once it’s found, it decreases it’s counter by m. If theID is not present, it prints 0. If the new count is less than or equal to 0, it deletes theID from the Red Black Tree. The complexity is O(log n).

void delete_id (int ID): This function deletes a node from the Red Black Tree. It then performs rotation and restructuring if any property of Red Black Tree is violated. f) void Count (int theID): This function searches for an element in the tree and if found, displays the count in the standard output stream. The element theID may or may not be present in the counter. If it is not present, the count is 0. The complexity is O(log n).

void InRange (int ID1, int ID2): This function searches for an ID within the range ID1 and ID2 (inclusive) and prints the sum of the counts of all the IDs within that range. The complexity of the algorithm is O (log n + s), where s is the number of elements in that range. h) void Next (int theID): This function prints the ID of the element with the smallest ID which is greater than theID. The complexity is O(log n).

void Previous(int theID): This function prints the ID of the element with the greatest ID which is smaller than theID. The complexity is O(log n).
