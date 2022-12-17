/**
 * Only the following includes are allowed in this file.
 *
 * Other includes may be used during development, but are expected to be
 * removed (not commented out) when the file is turned in to CodeGrade.
 */
#include "StoreStock.hpp"
#include <algorithm> // Don't have to be used, but is allowed

/**
 * Constructs a new StoreStock object so that it is in a valid state to be
 * used.
 */
StoreStock::StoreStock() {}

/**
 * Constructs a new StoreStock object as an exact copy of another StoreStock
 * object by creating and storing clones of all products in the other object.
 *
 * @param other An object to create a copy of.
 */
StoreStock::StoreStock(const StoreStock& other)
{
    for(auto& productPtr : other.products)
    {
        this->AddProduct(productPtr->Clone());
    }
}

/**
 * Sets the object in a destrubtable state.
 *
 * Frees all remainding products in the object.
 */
StoreStock::~StoreStock()
{
    for(auto& productPtr : this->products)
    {
        delete productPtr;
    }
}

/**
 * Makes the object an exact copy of another StoreStock object by freeing all
 * existing products and creating and storing clones of all products in the
 * other.
 *
 * @param other An object to become a copy of.
 * @returns A reference to the object itself.
 */
StoreStock& StoreStock::operator=(const StoreStock& other)
{
    if(this != &other)
    {
        for(auto it = begin(); it != end();)
        {
            delete *it;
            it = products.erase(it);
        }

        for(auto& productPtr : other.products)
        {
            this->AddProduct(productPtr->Clone());
        }
    }
    return *this;
}

/**
 * Getter the number of products in the object.
 *
 * @returns The number of products stored in the object.
 */
int StoreStock::GetSize() const
{
    return this->products.size();
}

/**
 * Accumulates the price of all existing products.
 *
 * @returns The total price of all products in the object.
 */
float StoreStock::GetTotalCost() const
{
    float tCost = 0;
    for(auto& productPtr : this->products)
    {
        tCost += productPtr->GetPrice();
    }
    return tCost;
}

/**
 * Adds a new product to the object.
 *
 * The passed pointer will be stored in the object without creating a clone
 * of the product. If the product pointer already exists in the object, it
 * will not be added again.
 *
 * @param product A pointer to a product to add.
 * @returns true if the product pointer didn't exist and could be added,
 * 			    otherwise false.
 */
bool StoreStock::AddProduct(Product* product)
{
    if(product != nullptr && !std::any_of(begin(), end(), [&product](const Product* elem) {
           return (elem == product);
       }))
        this->products.push_back(product);
    else
        return false;
    return true;
}

/**
 * Releases the responsibility an existing product from the object, without
 * freeing it from memory.
 *
 * Searches all existing product pointers in the object. If a matching pointer
 * is found, the object will forget about that pointer without deleting the
 * product, making the caller of this function responsible of managing the
 * memory of that product.
 *
 * @param product A pointer to a product to release.
 * @returns true if the product pointer exists and could be released,
 * 			    otherwise false.
 */
bool StoreStock::ReleaseProduct(Product* product)
{
    bool deleted = false;
    products.erase(std::remove_if(begin(), end(), [&product, &deleted](const Product* x) {
        deleted = true;
        return (x == product);
    }));
    return deleted;
}

/**
 * Retrieves the total amount of volume needed to store all products in the
 * object.
 *
 * Iterates all existing products and accumulates their storage volumes.
 *
 * @returns The total volume of all existing products in the object.
 */
float StoreStock::GetRequiredStorageVolume() const
{
    float tVolume = 0;
    for(auto& productPtr : this->products)
    {
        tVolume += productPtr->GetStorageVolume();
    }
    return tVolume;
}
