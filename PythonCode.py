import re
import string


# this function creates a dictionary using a for loop. It will loop through the txt file and add each item to the dictionary
# if an item is already in the dictionary it adds +1 to that dictionary keys value. This is used for option 1 in C++
def totalInventory():

    productList = {}

    openfile = open('ProductList.txt')
    inventory = openfile.readlines()

    for product in inventory:

        product = product.strip()
        if (product in productList):
            productList[product] += 1

        else:
            productList[product] = 1
    
    for key, value in productList.items():
        print (key, value)
    
# This function is used for option 2. Like the totalInventory function it will create a dictionary but this function takes a string 
# input from the user so once the dictionary is completed it will only print the value of the user input rather than the whole dictionary
def findItem(item):

    productList = {}

    openfile = open('ProductList.txt')
    inventory = openfile.readlines()

    for product in inventory:

        product = product.strip()
        if (product in productList):
            productList[product] += 1

        else:
            productList[product] = 1
    
    print(item, productList[item])
         
    return 0

# the writeFile function is used for option 3 and will open the original txt file, add it to a dictionary, and then  it will write it to a new .dat 
# file fully formatted so it can be read through C++
def writeFile():

    productList = {}

    openfile = open('ProductList.txt')
    
    inventory = openfile.readlines()

    for product in inventory:

        product = product.strip()
        if (product in productList):
            productList[product] += 1

        else:
            productList[product] = 1
    
    
    with open('frequency.dat', 'w') as f:
        for key, value in productList.items():
            f.write(key)
            f.write(' ')
            f.write( str(value))
            f.write('\n')
            
    f.close()
        
       
    
            
 
    


    