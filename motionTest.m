test = [2,94;94,2;30,16;16,30;17,76;76,17]
for i =1:length(test)
    moves = stepsToMove(test(i,1),test(i,2),95)
end

function [distance]= stepsToMove( startingNail, endingNail, NailNumber)
distance = 0;
%distance = NailNumber * (distance / NailNumber) - (distance % NailNumber)
if (endingNail < startingNail)
    distance = startingNail - endingNail;
    
    if (abs(distance) < NailNumber / 2)
        distance = -1 * distance;
    else
        distance = NailNumber - distance;
    end
else
    distance = NailNumber - endingNail + startingNail;
    if (abs(distance) < NailNumber / 2) 
        distance = -1 * distance;
    else
        distance = NailNumber - distance;
    end
end

end
