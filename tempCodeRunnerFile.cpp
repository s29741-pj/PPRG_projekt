    for (int iter = 0; iter < mazeFields.path_two.size(); iter++)
    {
        if(iter == 0)
            mazeFields.maze.at(mazeFields.path_two[iter]) = "$";
        else if(iter == mazeFields.path_two.size() - 1)
            mazeFields.maze.at(mazeFields.path_two[iter]) = "@";
        else    
            mazeFields.maze.at(mazeFields.path_two[iter]) = " ";
    }