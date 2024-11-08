#!/bin/bash

echo "Welcome to my address book..."
echo -n "Enter the address book name: "
read bname

if [ ! -e "$bname" ]; then
    touch "$bname"
    echo "Address book with the name $bname created successfully"
    echo -e "ID\t\tNAME\t\tMOBILE\t\tEMAIL" >> "$bname"
else 
    echo "Address book already exists!"
fi

while true; do
    echo ""
    echo "a. Display Address Book"
    echo "b. Insert a Record"
    echo "c. Delete a Record"
    echo "d. Modify a Record"
    echo "e. Exit"
    echo -n "Enter your choice: "
    read ch

    case $ch in
    a)
        cat "$bname"
        echo ""
        ;;
    b)
        echo -n "Enter ID: "; read id
        echo -n "Enter Name: "; read name
        echo -n "Enter Mobile: "; read mobile
        echo -n "Enter Email: "; read email
        echo -e "$id\t\t$name\t\t$mobile\t\t$email" >> "$bname"
        echo "Record inserted successfully."
        ;;
    c)
        echo -n "Enter the ID to be deleted: "; read did
        # -qw: q is for quiet and w is for word-regexp
        if grep -qw "$did" "$bname"; then
        # This option inverts the match.It tells grep to return lines that do not match the given pattern.
            grep -vw "$did" "$bname" > temp && mv temp "$bname"
            echo "Record deletion successful."
        else
            echo "Record with ID $did does not exist."
        fi
        ;;
    d)
        echo -n "Enter the ID to be modified: "; read mid
        if grep -qw "$mid" "$bname"; then
            grep -vw "$mid" "$bname" > temp && mv temp "$bname"
            echo -n "Enter new ID: "; read id
            echo -n "Enter new Name: "; read name
            echo -n "Enter new Mobile: "; read mobile
            echo -n "Enter new Email: "; read email
            echo -e "$id\t\t$name\t\t$mobile\t\t$email" >> "$bname"
            echo "Record modified successfully."
        else
            echo "Record with ID $mid does not exist."
        fi
        ;;
    e)
        echo "Thank you for using the address book!"
        exit 0
        ;;
    *)
        echo "Invalid choice. Please enter a valid option."
    esac
done