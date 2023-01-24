# Moosic
By: Andrew Goetz, George Wang, and Hunter Lauder

C++ Music application that allows seperate users (aside from primary user) and creation of friendships to recommend and listen to songs. Terminal commands are commented out in the beginning of main.cpp. Each meaningful function has runtime complexity commented. The system is created using the following ADTs illustrated below:

System Library - BST
Primary User Library - BST
A list of all users, whom:
has a friendship list - graph
song recommendation - Max Heap

# Testing
Python tester file called input.py is utilized to test all cases and demo code
To run in terminal (with n being a number starting from 0):
```
python3 input.py ./main t<n>
```

# Rubric
* A2 - Graph.h:59 Vertices stored in BST, Graph.h:13 edges stored in a linked list
* B5 - Library.h:34 SystemLib stored in BST, BST_ref.h:112 BST's find algorithm is O(logn)
* C4 - Graph.cpp:172 isFriend contains a BFS traversal implemenentation that traverses as far as depthLimit.
* D4 - Heap_Table.cpp:13 listen_toSong utilizes a function called sift_Up, which moves the position upward until it is smaller than its parent. Heap_Table.cpp:22 recommend utilizes a function called sift_Down, which moves the position downward until its smaller than its parent.

# Notes
* Users(vertices) are stored in a graph, the graph consists of a BST containing a linkedlist of friendships(edges). The BST used to store users are of type shared_ptr to help with marking visited when doing BFS with the graph. in each element of linked list, the edge is represented by a weak_ptr, who stores the corresponding shared_ptr in the BST.
* Recommendation system is stored in a Vector of shared_ptr of Songs, and in each songs contain a title, their corresponding position within the vector, and their play count.
* primary user's songs are stored in a normal BST, as such, all of its songs contain no more than just the title.
* System Library is a BST of references referring to songs inside the recommendation system indicated above. Doing so can simplify find to O(logn)
* radius is radius
