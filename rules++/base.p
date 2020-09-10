
///////////////////////////////////////
// presets
///////////////////////////////////////
/******************************************************************************

*/
preset Clear()

    OverrideLayer();
    Insert(0);
end



preset FillObjects(array object aObjects)
 
//
    if (s:debug)
        if (aObjects.count == 0)
            warning("preset.FillObjects(array object aObjects) -> aObjects was empty, function had no effect.");
            return;
        end
    end
//

    g:insertAllRotations = true;
    array object aArray = util:ConfigUpdateObjects(aObjects.unique(), g:updateInsert);
    g:insertAllRotations = false;

    for (i = 0 to aArray.last)
        coord cAnchor = aArray[i].anchor;
        
        for (j = 0 to aArray[i].last)
            coord cRelativePos = util:RelativePos(cAnchor, aArray[i][j]);
            
            Insert(aArray[i][j]).If(IndexAt([cRelativePos.x * -1, cRelativePos.y * -1]).Is(cAnchor));
        end
    end
end



preset Randomize(array int aIndices)

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("preset.Randomize(array int aIndices) -> aIndices was empty, function had no effect.");
            return;
        end
        
        for (i = 0 to aIndices.last)
            if (aIndices[i] < 0 or aIndices[i] > 255)
                warning("preset.Randomize(array int aIndices) -> values need to be in range [0-255].");
                return;
            end
        end
    end
//
    
    array int aArray = aIndices.unique();
    Insert(aArray[0]);
    Insert(aArray).Config(s:insertAllRotations).Chance(aArray.count * 4);
    Insert(aArray).Config(s:insertAllRotations).Chance(aArray.count * 8);
end



preset Randomize(array object aObjects)

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("preset.Randomize(array object aObjects) -> aObjects was empty, function had no effect.");
            return;
        end
    end
//
    
    array object aArray = aObjects.unique();
    for (i = 0 to aArray.last)
        InsertObject(aArray[i]).Config(s:insertAllRotations).If(Object().Config(s:checkAllRotations).HasSpace().IsNotEdge(top, right, bottom, left).IsNotOverlapping(aArray)).Chance(aArray.count * 8);
    end
end



preset RandomizeCustom(array int aIndices, array int aProbabilities)
    
//
    if (s:debug)
        if (aIndices.count == 0)
            warning("preset.RandomizeCustom(array int aIndices, array int aProbabilities) -> aIndices was empty, function had no effect.");
            return;
        end
        
        if (aProbabilities.count == 0)
            warning("preset.RandomizeCustom(array int aIndices, array int aProbabilities) -> aProbabilities was empty, function had no effect.");
            return;
        end
        
        if (aIndices.count != aProbabilities.count)
            warning("preset.RandomizeCustom(array int aIndices, array int aProbabilities) -> aIndices and aProbabilities weren't the same size, function had no effect.");
            return;
        end
        
        for (i = 0 to aIndices.last)
            if (aIndices[i] < 0 or aIndices[i] > 255)
                warning("preset.RandomizeCustom(array int aIndices, array int aProbabilities) -> values need to be in range [0-255].");
                return;
            end
        end
    end
//

    Insert(aIndices[0]);
    for (i = 0 to aIndices.last)
        Insert(aIndices[i]).Config(s:insertAllRotations).Chance(aProbabilities[i] * 8);
    end
end



preset Checkerboard(int iIndex1, int iIndex2)

//
    if (s:debug)
        if (iIndex1 < 0 or iIndex1 > 255)
            warning("preset.Checkerboard(int iIndex1, int iIndex2) -> iIndex1 needs to be in range [0-255].");
            return;
        end
        
        if (iIndex2 < 0 or iIndex2 > 255)
            warning("preset.Checkerboard(int iIndex1, int iIndex2) -> iIndex2 needs to be in range [0-255].");
            return;
        end
    end
//

    int iMask = iIndex1 + 1;
    if (iMask == iIndex2)
        iMask = iIndex2 + 1;
        if (iMask > 255)
            iMask = 1;
        end
    end
    if (iMask > 255)
        iMask = 1;
        if (iMask == iIndex2)
            iMask = iIndex2 + 1;
        end
    end
    
    OverrideLayer();
    Insert(iIndex1);
    Insert(iMask).If(IndexAt([0, 0]).IsEmpty(), IndexAt([-1, 0], [0, -1]).IsNot(iMask, iIndex2));
    Insert(iIndex2).If(IndexAt([0, 0]).Is(iIndex1), IndexAt([-1, 0], [0, -1]).IsNot(iMask, iIndex2));
    
    NewRun();
    Replace(iMask, 0);
end



preset ReplaceEachRotation(int iFrom, int iTo)

//
    if (s:debug)
        if (iFrom < 0 or iFrom > 255)
            warning("preset.ReplaceEachRotation(int iFrom, int iTo) -> iFrom needs to be in range [0-255].");
            return;
        end
        
        if (iTo < 0 or iTo > 255)
            warning("preset.ReplaceEachRotation(int iFrom, int iTo) -> iTo needs to be in range [0-255].");
            return;
        end
    end
//

    Insert(iTo).If(IndexAt([0, 0]).Is(iFrom.N));
    Insert(iTo.V).If(IndexAt([0, 0]).Is(iFrom.V));
    Insert(iTo.H).If(IndexAt([0, 0]).Is(iFrom.H));
    Insert(iTo.R).If(IndexAt([0, 0]).Is(iFrom.R));
    Insert(iTo.VH).If(IndexAt([0, 0]).Is(iFrom.VH));
    Insert(iTo.VR).If(IndexAt([0, 0]).Is(iFrom.VR));
    Insert(iTo.HR).If(IndexAt([0, 0]).Is(iFrom.HR));
    Insert(iTo.VHR).If(IndexAt([0, 0]).Is(iFrom.VHR));
end



preset RemoveDuplicates(array int aIndices)

//
    if (s:debug)
        if (aIndices.count < 2)
            warning("preset.RemoveDuplicates(array int aIndices) -> aIndices must have at least 2 values.");
            return;
        end
        
        for (i = 0 to aIndices.last)
            if (aIndices[i] < 0 or aIndices[i] > 255)
                warning("preset.RemoveDuplicates(array int aIndices) -> values need to be in range [0-255].");
                return;
            end
        end        
    end
//

    OverrideLayer();
    for (i = 0 to aIndices.last)
        int iIndex = aIndices[i];
        int iDefault = 0;
        
        if (i + 1 > aIndices.last)
            iDefault = aIndices[0];
        end
        if (i + 1 <= aIndices.last)
            iDefault = aIndices[i + 1];
        end
        
        for (j = 0 to aIndices.last)
            if (i != j)
                Insert(aIndices[j]).If(IndexAt([0, 0]).Is(iIndex), IndexAt([-1, 0]).Config(s:checkAllRotations).Is(iIndex)).Chance(aIndices.count - 1);
                Insert(aIndices[j]).If(IndexAt([0, 0]).Is(iIndex), IndexAt([0, -1]).Config(s:checkAllRotations).Is(iIndex)).Chance(aIndices.count - 1);
            end
        end
        Insert(iDefault).If(IndexAt([0, 0]).Is(iIndex), IndexAt([-1, 0]).Config(s:checkAllRotations).Is(iIndex));
        Insert(iDefault).If(IndexAt([0, 0]).Is(iIndex), IndexAt([0, -1]).Config(s:checkAllRotations).Is(iIndex));
    end
end
