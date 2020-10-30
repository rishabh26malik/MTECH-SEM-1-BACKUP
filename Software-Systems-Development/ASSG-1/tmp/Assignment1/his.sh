      1  history 10
      1  history 10 | awk '{$1=""; print $0}' | sort | uniq -c
      1  history 10 | awk '{$1=""; print $0}' | sort | uniq -c > his.txt
      1  history | sort -n | tail | awk '{$1=""; print $0}' | sed 's/ //g' | sort | uniq -c
      1  history | sort -n | tail | awk '{$1=""; print $0}' | sort | uniq -c
      2  ls -l | sed 's/ */ /g'
      1  ls -l | sed 's/ */ /g' | awk '{print $3}' | uniq
      1  ls -l | sed 's/ */ /g' | awk '{print $3}' | uniq -c
      1  ls -l | tr
