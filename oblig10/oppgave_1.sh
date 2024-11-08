#!/bin/bash

echo -n "Fornavn? "
read fornavn

antall=$(grep -i "^$fornavn" /etc/passwd | wc -l)
echo "Antall brukere som har navnet $fornavn: $antall"
