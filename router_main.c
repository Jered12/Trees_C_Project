#include "router_lib.h"  // Include router library header

int main() 
{ 
    // create a root for the router network tree, initially NULL
    RouterNode* root = NULL;
    // other support variables
    int option = 0, router_id;
    
    while (option != 9)
    {
        // print the menu
        printf("\nNetFlow: Router Traffic Management\n");
        printf("1. Add a new router\n");
        printf("2. Remove a faulty router\n");
        printf("3. Invert the router\n");
        printf("4. Ensure symmetrical routing\n");
        printf("5. Analyze maximum network depth\n");
        printf("6. Get right-side view of router network\n");
        printf("7. Identify high-traffic routers\n");
        printf("8. Print the network\n");
        printf("9. Exit\n");
        // prompt the user for input
        printf("Choose an option: ");
        // read the user's choice
        scanf("%d", &option);
        // choose the action based on user's choice
        switch (option)
        {
            // Task 1: Add a new router
            case 1:
            {
                do
                {
                    // prompt to enter router ID
                    printf("Enter router ID to add or -1 to exit: ");
                    // get the router ID from user
                    scanf("%d", &router_id);
                    if (router_id != -1)
                    {
                        // add router to network
                        addRouter(&root, router_id);
                    }
                } while (router_id != -1);
                // end case
                break;
            }
          
            // Task 2: Remove a faulty router
            case 2:
            {
                // prompt to enter router ID
                printf("Enter router ID to remove: ");
                // read the router ID from user
                scanf("%d", &router_id);
                // remove the router
                removeRouter(&root, router_id);
                // end case
                break;
            }
              
            // Task 3: Invert the router network
            case 3:
            {
                // print a message
                printf("Inverting the router network...\n");
                // invert router network
                root = invertNetwork(root);
                // if network is not empty
                if(root != NULL)
                {
                    // display success message
                    printf("Router network inverted successfully.\n");
                }
                // otherwise
                else
                {
                    // print error message
                    printf("Network is empty\n");
                }
                // end case
                break;
            }
            
            // Task 4: Ensure symmetrical routing
            case 4:
            {
                // if the network is symmetric
                if (isRoutingSymmetric(root))
                {
                    // print a message
                    printf("The routing is symmetrical.\n");
                }
                // otherwise
                else 
                {
                    // print error message
                    printf("Imbalanced routing detected.\n");
                }
                // end case
                break;
            }
            
            // Task 5: Analyze maximum network depth
            case 5:
            {
                // calculate the max depth of the network
                int maxDepth = getMaxNetworkDepth(root);
                // print a message
                printf("The maximum network depth is %d.\n", maxDepth);
                // end case
                break;
            }
            // Task 6: Get right-side view of router network
            case 6:
            {
                // initiate the count for the level
                int maxLevel = -1;
                // print the routers on the right
                getRouterRightView(root, 0, &maxLevel);
                // end case
                break;
            }
                
            // Task 7: Identify high-traffic routers
            case 7:
            {
                // find high-traffic routers
                findHighTrafficRouters(root);
                // end case
                break;
            }
                
            // Task 8: Show network
            case 8:
            {
                // print the message
                printf("Routers in the network: ");
                // print the network
                printNetwork(root);
                // end case
                break;
            }
                
            // exit case
            case 9:
            {
                // print a message
                printf("Exiting NetFlow Management System.\n");
                // end case
                break;
            }
            // default case for invalid input
            default:
            {
                // print an error message
                printf("Invalid option! Please try again.\n");
            }
        }
    }
}
