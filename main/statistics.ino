void statsMODE() {
  
     // change current project
      if(button == 4) {
        changeProject(-1);
        }

       if(button == 5) {
        changeProject(1);
        }

      if(!screen_interrupt) {
          line_one = "STATS: " + listOfProjects[currentProject];

          int timeSC = statsInt[currentProject];
          int statsTime[2] = {timeSC/60, timeSC-floor(timeSC/60)*60};
          line_two = String(statsTime[0]) + " h  " +  String(statsTime[1]) + " min";
        
      }
  
    
  }
