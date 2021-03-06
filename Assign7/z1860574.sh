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
newrecord()
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
       printf "***ERROR: Please enter a year after 1921 and before 2029***\n"
       exit 1
   fi
}   

# delete() function to remove records from a database
delete() 
{
    if [ $# = 1 ]; then
        printf "***ERROR: Please specify between all, single, or range to delete***\n"
        exit 1
    fi

        if [ "$2" = "all" ]; then
        sed -i '' '1!d' "$1"
        printf "All records deleted\n"

    elif [ "$2" = "single" ]; then
        sed -i '' $(($3 + 1))d "$1"
        printf "1 record deleted\n"

    elif [ "$2" = "range" ]; then
        sed -i '' $(($3 + 1)),$(($4 + 1))d "$1"
        printf "$(($4 - $3 + 1)) record(s) deleted\n"

    else
        printf "***ERROR: invalid delete argument: %s***\n" "$2"
        exit 1

    fi

}

# count() function used to count and print the number of rows in an existing database
count() 
{
    if [[ -f "$1" && -r "$1" ]]; then
        awks='{ print $1 }'
        temp=$(wc -l $1 | awk "$awks")
        printf "$((temp - 1))\n"
        
    else
        printf "****ERROR: %s cannot be read***\n" "$1"

    fi

}

cont="y"
while [ $cont = "y" ]; do
	# retrieve database name
	read -p "Select database file name: " dbName
	while [ -z "$dbName" ]; do
		read -p "Choose a database name: " dbName

	done

	read -p "Enter a command: newdb, newrecord, show, delete, count: " cmd

	if [ "$cmd" = "newdb" ]; then
		read -p "db header: " header
		if [ -z "$header" ]; then
			header="Untitled Database"

		fi

		newdb "$dbName" "$header"

	elif [[ $cmd = "newrecord" || $cmd = "add" ]]; then
		read -p "Make: " make
		read -p "Model: " model
		read -p "Year: " year
		read -p "Color: " color
		newrecord "$dbName" "$make" "$model" "$year" "$color"

	elif [ $cmd = "show" ]; then
		read -p "How many to show (one of all, single, or range): " howm
		if [ $howm = "single" ]; then
			read -p "Which single: " single
			show "$dbName" "$howm" "$single"

		elif [ $howm = "range" ]; then
			read -p "Begining of range: " beg
			read -p "End of range: " end
			show "$dbName" "$howm" "$beg" "$end"

		elif [ $howm = "all" ]; then
			show "$dbName" "$howm"

		else
			printf "***ERROR: %s  is not valid***\n" "$howm"

		fi

	elif [ $cmd = "count" ]; then
		count "$dbName"

	elif [ $cmd = "delete" ]; then
		read -p "How many to delete (one of all, single, or range): " howm
		if [ $howm = "single" ]; then
			read -p "Which single: " single
			delete "$dbName" "$howm" "$single"

		elif [ $howm = "range" ]; then
			read -p "Begining of range: " beg
			read -p "End of range: " end
			delete "$dbName" "$howm" "$beg" "$end"

		elif [ $howm = "all" ]; then
			delete "$dbName" "$howm"

		else
			printf "***ERROR: %s  is not valid***\n" "$howm"

		fi

	else
		printf "***ERROR: invalid command. Not: %s***\n" "$cmd"
		exit 1       

	fi

done

fi

exit 0 # sucess