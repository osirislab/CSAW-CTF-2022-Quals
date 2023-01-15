# dockREleakage


### TESTING NOTES [KIM]

* This challenge seemed really exciting to me at first because the scope of provided files was very nice; challenger provided more than a server file but not an overwhelming amount

* It was also nice to have to use the challenge description to navigate the files and think about what the challenge could be about

* Once you realize however the challenge can be solved by know extracting a tar file and base-64 decoding I was disappointed the challenge did not actually require more Docker knowledge

* Overall I really liked the challenge layout, but was hoping more would be required to solve it. Becuase of that I would say it's a VERY easy challenge, that does nonetheless teach an important message, even if in a very straigtforward way

<pre>SOLVED BY:<pre>
# Untaring file and just reading the p-flag.txt file to get second half of flag
# Examing the Dockerfile for base64 encoding of the first half of the flag
