# Save the header
head -8 npb_substrate.orig >header

# Add a modified version
echo "ITEM: ATOMS id type xu yu zu c_q[1] c_q[2] c_q[3] c_q[4] c_shape[1] c_shape[2] c_shape[3] mol" >> header
 
# delete the header + sort the atoms.
tail -n+10 npb_substrate.orig | sort -n > dump.tail

# create extra columns with the mol index
for i in {1..200}; do for j in {1..5}; do echo " $i"; done; done > mol

# Add the column with mol index.
paste -d "" dump.tail mol > pp

# Reconstruct the right file
cat header pp > npb_substrate.dump
rm -f pp mol dump.tail header
