void statsMODE() {
/*
      if((millis()-lastUpdated)>6000) { 
      String statsString = Statistics();
      
      int projectn=0;
      int start=0;
      int stopp=0;
      for(int i = 0; i<statsString.length(); i++) {
        if(statsString[i] == ';') {start=i;}
        if(statsString[i] == '#') {stopp=i;
        
        statisticsINT[projectn] = (statsString.substring(start+1, stopp)).toInt();
  
        projectn++;
        }
        
      }
      lastUpdated=millis();
      }*/
  
     // change current project
      if(button == 4) {
        changeProject(-1);
        }

       if(button == 5) {
        changeProject(1);
        }

      if(!screen_interrupt) {
          line_one = listOfProjects[currentProject];
          
          line_two = String(statsInt[currentProject]);
        
      }
  
  
      
  
  
  
  
  
  }
