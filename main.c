#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
    printf("ID: %d\nName: %s\nPrice: $ %.2f\n", prod.id, strtok(prod.name, "\n"), prod.price);
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
                Sleep(2000);
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

    Sleep(2000);
    menu();
}

void listProducts() {
    if(product_counter > 0) {
        printf("============ Products: ============\n");
        printf("===================================\n\n");
        for (int i = 0; i < product_counter; i++) {
            productInfo(products[i]);
            printf("==============================\n");
        }
        printf("\n");
        Sleep(2000);
        menu();
    } else {
        printf("There are no products in the database.\n");
        Sleep(2000);
        menu();
    }
}

void addToCart() {
    if(product_counter > 0) {
        printf("Please select a product from the list below:\n\n");
        Sleep(1000);
        printf("============ Products: ============\n");
        printf("===================================\n\n");
        for (int i = 0; i < product_counter; i++) {
            productInfo(products[i]);
            printf("==============================\n");
        }
        int id;
        scanf("%d", &id);
        getchar();

        int exists = 0;
        for(int i = 0; i < product_counter; i++) {
            if(products[i].id == id) {
                exists = 1;
                if(cart_counter > 0) {
                    int * res = productInCart(id);
                    if(res[0] == 1) {
                        cart[res[1]].quantity++;
                        printf("Quantity increased in cart for product: %s\n", cart[res[1]].product.name);
                        Sleep(2000);
                        menu();
                    } else {
                        Product p = getProductById(id);
                        cart[cart_counter].product = p;
                        cart[cart_counter].quantity = 1;
                        cart_counter++;
                        printf("Added new product to cart: %s\n", strtok(p.name, "\n"));
                        Sleep(2000);
                        menu();
                    }
                } else {
                    Product p = getProductById(id);
                    cart[cart_counter].product = p;
                    cart[cart_counter].quantity = 1;
                    cart_counter++;
                    printf("Added new product to cart: %s\n", strtok(p.name, "\n"));
                    Sleep(2000);
                    menu();
                }
            }
        }
        if(exists < 1) {
            printf("ID no. %d not found in product database.\n", id);
            Sleep(2000);
            menu();
        }

    } else {
        printf("There are no products in the database.\n");
        Sleep(2000);
        menu();
    }
}

void goToCart() {
    if(cart_counter > 0) {
        printf("Products added to cart:\n");
        printf("=======================\n");
        for(int i = 0; i < cart_counter; i++) {
            productInfo(cart[i].product);
            printf("Quantity: %d\n", cart[i].quantity);
            printf("=============\n");
        }
        Sleep(2000);
        menu();
    } else {
        printf("The cart is empty.\n");
        Sleep(2000);
        menu();
    }
}

Product getProductById(int id) {
    Product p;
    for(int i = 0; i < product_counter; i++) {
        if(products[i].id == id) {
            p = products[i];
        }
    }
    return p;
}

int * productInCart(int id) {
    int static res[] = {0, 0};
    for(int i = 0; i < cart_counter; i++) {
        if(cart[i].product.id == id) {
            res[0] = 1;
            res[1] = i;
        }
    }
    return res;
}

void checkout() {
    if(cart_counter > 0) {
        float total = 0.0;
        printf("Products added to cart:\n");
        printf("=======================\n");
        for(int i = 0; i < cart_counter; i++) {
            Product p = cart[i].product;
            int quantity = cart[i].quantity;
            total += p.price * quantity;
            productInfo(p);
            printf("Quantity: %d\n", quantity);
            printf("=============\n");
        }
        printf("Your total is $ %.2f\n", total);
        Sleep(3000);
        cart_counter = 0;
        printf("Thank you for your patronage!\n");
        Sleep(3000);
        menu();
    } else {
        printf("Your cart is currently empty!\n");
        Sleep(3000);
        menu();
    }
}