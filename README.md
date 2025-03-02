# Double-Threaded AVL Tree Library

This library provides a generic Double-Threaded AVL Tree (Double-Threaded Self Balancing Binary Search Tree) implementation, which efficiently supports operations such as **insertion**, **deletion**, **searching**, and **updating** of nodes. It maintains a balanced binary search tree structure, ensuring that the tree remains balanced after each modification. This helps optimize search times and ensures logarithmic time complexity for insertion, deletion, and lookup operations. Since this is genric, users need to implement the custom nodes, an example for which is provided (Stock manager).

## Key Features
- **AVL Tree Property**: The tree is an **AVL (Adelson-Velsky and Landis)** tree, which ensures that the difference in heights of left and right subtrees of any node is at most `1`. This ensures the tree remains balanced, providing efficient access and modification times.
  
- **Double Threading**: The tree uses **double-threading**, where each node in the tree contains pointers to both its **left** and **right** children, and also to **previous** and **next** nodes, forming a doubly linked list. This allows for efficient in-order traversal and faster access to neighboring nodes without needing additional traversals.

## Core Operations

### 1. **Insert**  
Inserts a new node into the AVL tree while maintaining balance.  
Time Complexity: **O(log n)**

### 2. **Delete**  
Deletes an existing node and rebalances the tree to preserve the AVL property.  
NOTE: User is resposnible to free the memory. The node is returned from the function. This help user to manage the memory of the associated custom node (say a char * data member) 
Time Complexity: **O(log n)**

### 3. **Search**  
Searches for a given node in the tree. Returns a pointer to the node if found.  
Time Complexity: **O(log n)**

### 4. **Update**  
Replaces an existing node with a new one while ensuring the AVL property is maintained.  
Time Complexity: **O(log n)**

### 5. **Traversal**  
In-order and pre-order traversals are available. The in-order traversal is facilitated by the double-threading, making it faster to access the next node in sequence.  
Time Complexity: **O(n)** (for full tree traversal)

### 6. **Walk**  
Walk through the tree applying an action function (function pointer passed as a param) to each node in the order.  
Time Complexity: **O(n)** (for full tree traversal)

## Tree Structure and Nodes

Each node (`TreeNode`) in the tree contains:
- **Pointers to left, right, previous, and next nodes**, forming a doubly linked list to support efficient traversal.
- **Height** to assist in balancing the tree.
- **Node comparison function** that is used to determine the placement of nodes during insertions and deletions.

The tree (`Tree`) itself provides:
- **Root**, **First**, and **Last** pointers for fast access to the tree’s first and last nodes.
- **Node count** for efficient tracking of the tree size.

## Balancing and Rotations

The AVL tree maintains its balance by performing rotations:
- **Left Rotate**: Used when a right-heavy subtree needs to be balanced.
- **Right Rotate**: Used when a left-heavy subtree needs to be balanced.
- **Left-Right and Right-Left Rotations**: Handle more complex balancing cases by combining left and right rotations.

## How Double-Threading Works

- **In-Order Traversal**: Double-threading makes in-order traversal highly efficient. Each node has a pointer to its **previous** and **next** neighbors, allowing for easy access to the next node without traversing the entire subtree again.
  
- **Fast Access to Neighbors**: Double-threading reduces the need to traverse multiple levels of the tree when moving between neighboring nodes. This can be especially useful in scenarios where quick traversal and neighbor access are required.

# Stock Management System

This example demonstrates how to implement custom functionality on top of a generic double-threaded AVL tree. The focus here is on managing stock data using a tree structure. The custom implementation involves creating a `StockNode` class to store stock information (name and quantity), and performing various operations on it using AVL trees.

### Overview

- **StockNode**: A class that represents a node in the tree, where each node holds stock information, including the stock name and stock quantity.
- **StockMgr**: A class for managing stock operations, such as inserting, deleting, updating, searching, and displaying stock information.
- **AVL Tree**: A balanced binary search tree (BST) used for efficient searching, insertion, and deletion of stocks. In this implementation, we are using a **double-threaded AVL tree** (a specific type of AVL tree that also maintains thread pointers for efficient traversal).
- Other input/string utils.

### Structure

1. **StockNode Class**:
    - Stores stock details: name (`char* vStockName`) and quantity (`int vStock`).
    - Provides methods for comparing nodes based on stock name or quantity.
    - Supports insertion, copying, and deletion operations while managing dynamic memory for stock names.

2. **StockMgr Class**:
    - Manages the stock data by using two AVL trees:
        - One AVL tree for stock names (sorted by stock name).
        - One AVL tree for stock quantities (sorted by stock quantity).
    - Includes a menu-based interface for interacting with the stock data (insert, delete, update, etc.).

### Key Methods in `StockNode`

- **Constructor/Destructor**: Initializes the stock name and quantity. Destructor cleans up dynamically allocated memory for the stock name.
- **CopyStock**: Copies data from another `StockNode`.
- **CmprName**: A static comparison function that compares stock names.
- **CmprStock**: A static comparison function that compares stock quantities.
- **Print**: Prints stock information.

### Key Methods in `StockMgr`

- **StockMenu**: Displays a menu for managing stocks and allows the user to select various operations.
- **InsertStock**: Allows the user to insert a new stock into the system, ensuring stock names are unique.
- **DeleteStock**: Deletes a stock based on the given stock name.
- **UpdateStock**: Allows the user to update stock details (name/quantity).
- **Search**: Allows the user to search for a stock by name and display its details.
- **PrintAll**: Prints all stock information.

### Why Two Trees?

At first glance, managing two separate trees may seem redundant, but it provides a significant performance boost for certain operations, allowing for efficient data management. Here’s why:

1. **Efficiency in Search Operations (O(log n))**:
   - By having a **separate tree for stock names** and another for stock quantities (or dates), you can **efficiently search for stocks based on different criteria** without having to traverse the entire dataset.
   - Searching for a stock by name or by quantity can be done in **O(log n)** time, which is a significant improvement compared to linear search methods.

2. **Efficient Insertion and Deletion**:
   - Insertion and deletion operations also maintain **O(log n)** complexity for both trees.
   - When you insert or delete a stock by **name**, the system performs the operation in the **stock name tree**. Similarly, for operations based on **stock quantity**, the relevant operation is done in the **quantity tree**.
   - Since both trees are balanced AVL trees, each insertion or deletion is performed in **logarithmic time**, ensuring that the system remains efficient even as the number of stocks increases.

3. **Dual Indexing**:
   - The use of two trees effectively creates **dual indexing** for stock data, which allows for multiple efficient access patterns. You can:
     - **Search by name** quickly using the stock name tree.
     - **Filter or search by quantity (or date)** quickly using the stock quantity tree.
   - This dual-indexing approach provides flexibility in how stocks can be accessed, filtered, and displayed, without compromising performance.

4. **Filter Operations**:
   - You can easily perform filters or searches based on stock **quantity or date**. For example, you can find stocks that have **the lowest quantities** by querying the **stock quantity tree**, and it will return the lowest quantity stock in **O(log n)** time.
   - Similarly, you can implement filters to display stocks that have quantities **greater than a certain threshold**, or **sort stocks** based on quantities.
