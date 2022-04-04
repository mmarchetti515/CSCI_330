# Assign 7 Automobile database shell 
# Michael Marchetti z1860574
# csci330
#!/bin/bash

# newdb() function used to create new database taking two param
newdb()
{
	printf "%s\n" "$2" > "$1"
	printf "Database"
	printf $1
	printf "created"
}


# newrecord() function used to add a record to an existing database file always taking 5 param exactly
newrecord() #
{
    if [[ "$4" -gt 1921 && "$4" -lt 2029 ]]; then
	    if [[ ! -z "$2" && ! -z "$3" && ! -z "$5" ]]; then
		    printf "%s, %s, %s, %s\n" "$2" "$3" "$4" "$5" >> "$1"
                        printf "New record added!\n"
	    else
	        printf "***ERROR: Please enter a value with at least one character***\n"
                exit 1
           fi
   else
       printf "**ERROR: Please enter a year after 1921 and before 2029***\n"
       exit 1
   fi
}   

# show() function used to show existing record(s) in a database file taking up to 4 param
show()
{
	printf "$1 \n"
	printf "$2, $3, $4, $5"
}	

# delete() function used to delete records from an existing database


# count() function used to count and print num rows in a database always taking 1 param exactly

