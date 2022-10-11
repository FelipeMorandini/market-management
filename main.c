#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.c>

typedef struct {
    int id;
    char name[30];
    float price;
} Product;

typedef struct {
   Product product;
   int quantity; 
} Cart;

void productInfo(Product prod);
void menu();
void createProduct();
void listProducts();
void addToCart();
void goToCart();
Product getProductById(int id);
int * productInCart(int id);
void checkout();

static int product_counter = 0;
static int cart_counter = 0;
static Cart cart[50];
static Product products[50];


int main() {
    menu();
    return 0;
}

void productInfo(Product prod) {
    printf("ID: %d\nName: %s\nPrice: $ %.2f", prod.id, strtok(prod.name, "\n"), prod.price);
}

void menu() {
    printf("=================================================\n");
    printf("=================== Welcome! ====================\n");
    printf("========== Shopping Management System ===========\n");
    printf("=================================================\n\n");

    printf("What do you want to do?\n");
    printf("1 - Create product\n");
    printf("2 - List products\n");
    printf("3 - Add product to cart\n");
    printf("4 - See cart\n");
    printf("5 - Checkout\n");
    printf("6 - Quit\n");

    int choice;
    scanf("%d", &choice);
    getchar();

    switch(choice) {
        case 1:
            createProduct();
            break;
        case 2:
            listProducts();
            break;
        case 3:
            addToCart();
            break;
        case 4:
            goToCart();
            break;
        case 5:
            checkout();
            break;
        case 6:
            printf("Are you sure you want to quit? [Y/N]\n");
            char sure;
            scanf("%c", &sure);
            sure = toupper(sure);
            getchar();

            while(sure != 'Y' && sure != 'N') {
                printf("Please enter a valid option!\n");
                printf("Are you sure you want to quit? [Y/N]\n");
                scanf("%c", &sure);
                sure = toupper(sure);
                getchar();
            }

            if(sure == 'Y') {
                printf("Thank you for using our app!");
                Sleep(2);
                exit(0);
            } else {
                break;
            }
        default:
            printf("Please enter a valid option!\n");
            break;
    }
}

void createProduct() {
    printf("========== Create a product: ==========\n");
    printf("=======================================\n\n");

    printf("Enter the product's name:\n");
    fgets(products[product_counter].name, 30, stdin);

    printf("Enter the product's price:\n");
    scanf("%f", &products[product_counter].price);

    printf("Successfully created the following product: %s\n", strtok(products[product_counter].name, "\n"));

    products[product_counter].id = product_counter+1;
    product_counter++;
}

void listProducts() {
    if(product_counter > 0) {
        printf("============ Products: ============\n");
        printf("===================================\n\n");
        for (int i = 0; i < product_counter; i++) {
            productInfo(products[i]);
            printf("==============================\n");
            sleep(1);
        }
    } else {
        printf("There are no products in the database.");
    }
}

void addToCart() {

}

void goToCart() {

}

Product getProductById(int id) {

}

int * productInCart(int id) {

}

void checkout() {

}