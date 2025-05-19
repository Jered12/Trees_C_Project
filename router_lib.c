#include "router_lib.h"

/**
 * Task 1: Add a New Router
 * Input argument: root - a double pointer to the root of the network
 *                 router_id - the identification for the new router
 * Output argument: the last unfilled position of the last level contains a new
 *                  router with id router_id
 * Return: none
 * Dependencies: createRouter, createQueue, isEmptyQueue, enqueue, dequeue
 */
void addRouter(RouterNode** root, int router_id){
    //create a new router with the id that was given
    RouterNode* newRouter =createRouter(router_id);
    //if there is nothing in the root node
    if (*root ==NULL) 
    {
        //the new router is the node
        *root=newRouter;
        //and return
        return;
    }
    
    // create a queue
    Queue queue=createQueue();
    //add the root in the queue
    enqueue(&queue,*root);
    
    // while the queue is not empty
    while (!isEmptyQueue(&queue)) 
    {
        //create a current node that holds the front of the queue
        RouterNode* currentNode =dequeue(&queue);
    
         // now if the left child is empty
        if (currentNode->left ==NULL) 
        {
            //add the new router into the left child
            currentNode->left=newRouter;
            //exit
            return;  
        } 
        //if the left child is not empty enque the lft childinto the queue
        enqueue(&queue,currentNode->left);
    
        // then if the right child is empty
        if (currentNode->right==NULL) 
        {
            //add the new router into the right child
            currentNode->right =newRouter;
            //exit
            return;  
        }
        //if the right child is not empty enque the right child into the queue
        enqueue(&queue, currentNode->right); 
    }
}

/**
 * Task 2: Remove a Faulty Router
 * Input argument: root - a double pointer to the root of the network
 *                 router_id - the identification for the new router
 * Output argument: the target router is replaced with the last router in the 
 *                   network (bottomost, rightmost node)
 * Return: none
 * Dependencies: createQueue, isEmptyQueue, enqueue, dequeue
 *               stdlib.h - free
 */

void removeRouter(RouterNode** root, int router_id){
    //create a queue
    Queue queue=createQueue();
    //add all the stuff from the root to the queue
    enqueue(&queue, *root);

    //initlize last node of the tree so that we can swap after
    RouterNode* lastNode =NULL;
    //initlize the lasts parent node so that we swpa correctlu
    RouterNode* lastParentNode =NULL;
    //initilize the taget router to be found
    RouterNode* targetRouter =NULL;

    //while the queue is ont empty
    while (!isEmptyQueue(&queue)) 
    {
         //dequee the front node which will be the current node
        RouterNode* currentNode =dequeue(&queue);
       
        //if the current node is the router id we are looking for
        if (currentNode->router_id ==router_id) 
        {
            //make the curreny node the target node we are lookking for
            targetRouter =currentNode; 
        }
        //now if the cuurent node has a left child
        if (currentNode->left) 
        {
            //make the current node the last parent
            lastParentNode =currentNode;
            //make last now look at the left child
            lastNode =currentNode->left;
            //add the laft child into the queue
            enqueue(&queue,currentNode->left);
        }
        //then if the cuurent node has a right child
        if (currentNode->right) 
        {
            //make the current node the last parent
            lastParentNode =currentNode;
            //make last now look at the right child
            lastNode =currentNode->right;
            //add the right child into the queue
            enqueue(&queue,currentNode->right);
        }
        
        
    }
    //if the target is not found
    if (targetRouter!=NULL) 
    {
        //replace target node  with last
        targetRouter->router_id =lastNode->router_id;

        //if the last node is the right child of the last parent
        //if its the rightmost node
        if (lastParentNode->right==lastNode) 
        {
            //then disconnect the right child from the parent
            lastParentNode->right =NULL;
        } 
        else 
        {
            //else disconnect left child from the parent
            lastParentNode->left =NULL;
        }
        //finally free the last node
        free(lastNode);
        //print message
        printf("Router with ID %d successfully removed.\n", router_id);
    }
    else
    {
        //print message and retuen
        printf("Router with ID %d not found.\n", router_id);
        return;
    }
}


/**
 * Task 3: Invert Router Network
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: the pointer to the root node, where the tree's left and right sides 
 *          are swapped
 * Dependencies: invertNetwork (recursive)
 */

RouterNode* invertNetwork(RouterNode* root){
    //if the root is empty
    if (root==NULL) 
    {
        //return null
        return NULL;
    }

    // craete a new node that hold tempararay nodes that holds the left child
    RouterNode* temparary =root->left;
    //add the right child to the left childs
    root->left =root->right;
    //add the temparary nodes that hold the left child into the right child
    root->right =temparary;

    // Recursively invert the left subtree
    invertNetwork(root->left);
    // Recursively invert the right subtree
    invertNetwork(root->right);

    //finally return the root thats inverted
    return root;

}

/**
 * Task 4: Ensure Symmetrical Routing
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: true if the routing is symmetric, false otherwise
 * Dependencies: createQueue, enqueue, dequeue, isEmptyQueue
 */

bool isRoutingSymmetric(RouterNode* root){
    //if there is nothing in the root(empty)
    if (root ==NULL) 
    {
        //the tree is then symetrical
        return true; 
    }
    //create the queue
    Queue queue =createQueue();
    //then add(enqueue ) the root twice to start check
    enqueue(&queue ,root);
    enqueue(&queue,root);
    //while the queue is not empty
    while (!isEmptyQueue(&queue)) 
    {
        //dequeu the two queues into diffrent nodes to compare
        RouterNode* firstSymetry =dequeue(&queue);
        RouterNode* secondSymetry =dequeue(&queue);

        //if only one is null and the other is not
        if (firstSymetry== NULL || secondSymetry== NULL) 
        {
            //then its not symmetric
            return false; 
        }

        // enque the left child of the first symetu
        enqueue(&queue,firstSymetry->left);
        // enque the right child of the second symetu
        enqueue(&queue,secondSymetry->right);
        // enque the right child of the first symetu
        enqueue(&queue,firstSymetry->right);
        // enque the left child of the second symetu
        enqueue(&queue,secondSymetry->left);
    }
    //if everything passed then its symetric
    return true;
}

 

/**
 * Task 5: Analyze Maximum Network Depth
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: an integer value representing the maximum depth of the tree
 * Dependencies: getMaxNetworkDepth (recursive)
 */

int getMaxNetworkDepth(RouterNode* root){
    //if the tree is empty
    if (root ==NULL) 
    {
        //return 0 which is the base case when there are no levels
        return 0;  
    }
    //declare a variable to hold the left subtree
    int depthOfLeftSide;
     //declare a variable to hold the right subtree
    int depthOfrightSide;

    // recursively find the maximum depth of the left subtrees
    depthOfLeftSide =getMaxNetworkDepth(root->left);
    // recursively find the maximum depth of the right subtrees
    depthOfrightSide =getMaxNetworkDepth(root->right);

    // if the left side is greater than the right
    if (depthOfLeftSide > depthOfrightSide) 
    {
        //add 1 to the left subtree count
        return depthOfLeftSide+1;
    } 
    else 
    {
        //else add 1 to the right subtree count
        return depthOfrightSide+1;
    }
}

/**
 * Task 6: Get a Right-Side View of the Router Network
 * Input argument: root - a pointer to the root of the network
 *                 level - an integer representing the current level (root is 
 *                         at level 0)
 *                  maxLevel - an integer value representing the last level 
 *                         (initially set to -1)
 * Output argument: none
 * Return: none
 * Dependencies: getRouterRightView (recursive)
 *               stdio.h - printf
 */

void getRouterRightView(RouterNode* root, int level, int* maxLevel){
    //if there is nothing is the current node
    if (root ==NULL)
    {
        //base case so return
        return;
    }
    // if the level is bigger than the max 
    if (level >*maxLevel) 
    {
        //then print the node
        printf("%d ", root->router_id);
        //make this level the max level
        *maxLevel =level;  
    }

    // go through the right subtree to find the rightmost node
    getRouterRightView(root->right,level + 1, maxLevel);
}

/**
 * Function: findHighTrafficRouters
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: none
 * Dependencies: createQueue, enqueue, dequeue, isEmptyQueue
 *               stdio.h - printf
 */

void findHighTrafficRouters(RouterNode* root){
    //create a new quque
    Queue queue= createQueue();
    //add the root to the queue
    enqueue(&queue,root);
    //now while the queu is not empty
    while (!isEmptyQueue(&queue)) 
    {
        //initilize a variable to check the amount of nodes in each level
        int nodeAmountEachLevel =0;
        //start the current node fron the front
        QueueNode* currentNode = queue.front;
        
        // while there are nodes in the levek
        while (currentNode != NULL) 
        {
            //increase the size
            nodeAmountEachLevel++;
            //go to the next node
            currentNode =currentNode->next;
        }
        //create new variable to hold the max traffic
        int currentMaxTraffic =0;
        //for loop throuh all the nodes
        for (int index = 0; index < nodeAmountEachLevel; index++) 
        {
            //now remove the front node and add it to the temparary
            RouterNode* temparay =dequeue(&queue);
            //if the current node is bigger than the max traffic
            if (temparay->router_id > currentMaxTraffic) 
            {
                //make the max traffic the current node
                currentMaxTraffic =temparay->router_id;
            }
            //if the current node has a left child
            if (temparay->left)
            {
                //add that child to the queue
                enqueue(&queue,temparay->left);
            } 
            //if the current node has a right child
            if (temparay->right)
            {
                //add that child to the queue
                enqueue(&queue,temparay->right);
            } 
        }
        //print the max traffic
        printf("%d ",currentMaxTraffic);
    }

}


/**
 * Task 8: Show Routers
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */

void printNetwork(RouterNode* root){
    //create a new queue
    Queue queue=createQueue();
    //add the root to the queu
    enqueue(&queue,root);
    //while the queue isn not empty
    while (!isEmptyQueue(&queue)) 
    {
        //remove the front of the queue and add it to the current node
        RouterNode* currentNode= dequeue(&queue);
        //not print the current node routed id
        printf("%d ",currentNode->router_id);
        //if the left child of the current node exists
        if (currentNode->left!= NULL) 
        {
            //add it to the queeu so be used
            enqueue(&queue, currentNode->left);
        }
        //if the right child of the current node exists
        if (currentNode->right != NULL) 
        {
            //add it to the queeu so be used
            enqueue(&queue,currentNode->right);
        }
    }
} 


// utility functions
/**
 * Function: createRouter
 * Input argument: router_id - the router's identification
 * Output argument: none
 * Return: a pointer to the recently created router node with no children
 * Dependencies: stdlib.h - malloc
 */

RouterNode* createRouter(int router_id){
    // allocate memory for the router node
    RouterNode* newRouter = (RouterNode*)malloc(sizeof(RouterNode));
    
    // Initialize the router node
    newRouter->router_id = router_id;
    //make the left of the router null
    newRouter->left = NULL;
    //make the right of the router null
    newRouter->right = NULL;
    
    // return the new router node
    return newRouter;
}

/**
 * Function: createQueue
 * Input argument: none
 * Output argument: none
 * Return: a queue where front and rear pointers are set to NULL
 * Dependencies: none
 */

Queue createQueue(){
    //inititlize a new queue
    Queue queue;
    //make the front and rear of the queue null
    queue.front =NULL;
    queue.rear =NULL;
    //return the queue
    return queue;
    
}

/**
 * Function: isEmptyQueue
 * Input argument: queue - a pointer to a queue
 * Output argument: none
 * Return: true if the queue is empty, false otherwise
 * Dependencies: none
 */
bool isEmptyQueue(Queue* queue){
    //if the front is NULL it means the queue is empty
    return queue->front==NULL;
}


/**
 * Function: enqueue
 * Input argument: queue - a pointer to a queue
 *                 router - a pointer to the router node to enqueue
 * Output argument: the router is added at the rear of the queue
 * Return: none
 * Dependencies: stdlib.h - malloc
 */

void enqueue(Queue* queue, RouterNode* router){
    // Allocate memory for a new queue node
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));

    // Initialize the new queue node
    newNode->router = router;
    //make the next node NULL
    newNode->next = NULL;
    //if the raer is empty
    if (queue->rear == NULL) 
    {
        //the froont should be the new node
        queue->front = newNode;
        //and the raer should be the new node
        queue->rear = newNode;
    } 
    else 
    {
        // else add the new node at the rear of the queue
        queue->rear->next = newNode;
        //update the raer
        queue->rear = newNode;
    }
}  

/**
 * Function: dequeue
 * Input argument: queue - a pointer to a queue
 * Output argument: the front router is removed from the queue
 * Return: a pointer to the dequeued router node (not the queue node!)
 *         NULL if the queue is empty
 * Dependencies: isEmptyQueue
 *               stdlib.h - free
 */
RouterNode* dequeue(Queue* queue){
     
    // add the front node into a temporaray variable
    QueueNode* temporaray= queue->front;
    // Save the string value which is the deleted or dequeued value
    RouterNode* deletedValue =temporaray->router; 

    // move the front variable one to the right
    queue->front =queue->front->next;

    // if the queue is empty
    if (queue->front== NULL) 
    {
        //then the back is empty
        queue->rear =NULL;
    }

    // Return the deleted or dequed value
    return deletedValue; 
}
