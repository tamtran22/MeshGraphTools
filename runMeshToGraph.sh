mkdir processed/
for fname in $(ls *.dat); do
    ./meshToGraph.exe $fname ./processed/$fname
done