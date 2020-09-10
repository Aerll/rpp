
///////////////////////////////////////
// NYI
// - tests for borders around the tiles
// - InsertObject.At(coord)

///////////////////////////////////////
// global variables (internal)
///////////////////////////////////////
/******************************************************************************

*/
// settings
bool g:checkAllRotations  = false;
bool g:checkOnlyRotations = false;
bool g:checkOnlyMirrors   = false;

bool g:checkV   = false;
bool g:checkH   = false;
bool g:checkR   = false;
bool g:checkN   = false;
bool g:checkVH  = false;
bool g:checkVR  = false;
bool g:checkHR  = false;
bool g:checkVHR = false;

bool g:insertAllRotations  = false;
bool g:insertOnlyRotations = false;
bool g:insertOnlyMirrors   = false;

bool g:insertV   = false;
bool g:insertH   = false;
bool g:insertR   = false;
bool g:insertN   = false;
bool g:insertVH  = false;
bool g:insertVR  = false;
bool g:insertHR  = false;
bool g:insertVHR = false;

bool s:debug = true;

// flags
int g:resetCheck  = 1000;
int g:resetInsert = 1001;

int g:updateCheck  = 2000;
int g:updateInsert = 2001;

int g:getCheck  = 3000;
int g:getInsert = 3001;

// value holders
int g:vInsertIndex = 0;
object g:vInsertObject;

// values
int g:intMax = 2147483647;
int g:intMin = -2147483648;



function->null util:ResetSettings(int iResetFlag)

    if (iResetFlag == g:resetCheck)
        g:checkAllRotations  = false;
        g:checkOnlyRotations = false;
        g:checkOnlyMirrors   = false;

        g:checkV   = false;
        g:checkH   = false;
        g:checkR   = false;
        g:checkN   = false;
        g:checkVH  = false;
        g:checkVR  = false;
        g:checkHR  = false;
        g:checkVHR = false;
    end
    if (iResetFlag == g:resetInsert)
        g:insertAllRotations  = false;
        g:insertOnlyRotations = false;
        g:insertOnlyMirrors   = false;

        g:insertV   = false;
        g:insertH   = false;
        g:insertR   = false;
        g:insertN   = false;
        g:insertVH  = false;
        g:insertVR  = false;
        g:insertHR  = false;
        g:insertVHR = false;
    end
end



///////////////////////////////////////
// settings
///////////////////////////////////////
/******************************************************************************

*/
// pos rules
int s:checkAllRotations  = 10000;
int s:checkOnlyRotations = 10001;
int s:checkOnlyMirrors   = 10002;

int s:checkV   = 10003;
int s:checkH   = 10004;
int s:checkR   = 10005;
int s:checkN   = 10006;
int s:checkVH  = 10007;
int s:checkVR  = 10008;
int s:checkHR  = 10009;
int s:checkVHR = 10010;



// rules
int s:insertAllRotations  = 20000;
int s:insertOnlyRotations = 20001;
int s:insertOnlyMirrors   = 20002;

int s:insertV   = 20003;
int s:insertH   = 20004;
int s:insertR   = 20005;
int s:insertN   = 20006;
int s:insertVH  = 20007;
int s:insertVR  = 20008;
int s:insertHR  = 20009;
int s:insertVHR = 20010;



// other
int s:noDefaultRule = 30000;



///////////////////////////////////////
// utility functions
///////////////////////////////////////
/******************************************************************************

*/
function->array bool util:ArrayBool(array bool aValues) 

    return aValues;
end

function->array int util:ArrayInt(array int aValues) 

    return aValues;
end

function->array coord util:ArrayCoord(array coord aValues) 

    return aValues;
end

function->array range util:ArrayRange(array range aValues) 

    return aValues;
end

function->array float util:ArrayFloat(array float aValues) 

    return aValues;
end

function->array string util:ArrayString(array string aValues) 

    return aValues;
end

function->array object util:ArrayObject(array object aValues) 

    return aValues;
end



function->int util:RemoveRotation(float fIndex)

    return fIndex;
end



function->null util:ConfigUpdate(array int aSettings, int iFlag)

    if (aSettings.count == 0) 
        return;
    end

    for (i = 0 to aSettings.last)
        int iSetting = aSettings[i];
        
        if (iFlag == g:updateCheck)
            if (iSetting == s:checkAllRotations)  g:checkAllRotations  = true; end
            if (iSetting == s:checkOnlyRotations) g:checkOnlyRotations = true; end
            if (iSetting == s:checkOnlyMirrors)   g:checkOnlyMirrors   = true; end
            if (iSetting == s:checkV)             g:checkV             = true; end
            if (iSetting == s:checkH)             g:checkH             = true; end
            if (iSetting == s:checkR)             g:checkR             = true; end
            if (iSetting == s:checkN)             g:checkN             = true; end
            if (iSetting == s:checkVH)            g:checkVH            = true; end
            if (iSetting == s:checkVR)            g:checkVR            = true; end
            if (iSetting == s:checkHR)            g:checkHR            = true; end
            if (iSetting == s:checkVHR)           g:checkVHR           = true; end
        end
        if (iFlag == g:updateInsert)
            if (iSetting == s:insertAllRotations)  g:insertAllRotations  = true; end
            if (iSetting == s:insertOnlyRotations) g:insertOnlyRotations = true; end
            if (iSetting == s:insertOnlyMirrors)   g:insertOnlyMirrors   = true; end
            if (iSetting == s:insertV)             g:insertV             = true; end
            if (iSetting == s:insertH)             g:insertH             = true; end
            if (iSetting == s:insertR)             g:insertR             = true; end
            if (iSetting == s:insertN)             g:insertN             = true; end
            if (iSetting == s:insertVH)            g:insertVH            = true; end
            if (iSetting == s:insertVR)            g:insertVR            = true; end
            if (iSetting == s:insertHR)            g:insertHR            = true; end
            if (iSetting == s:insertVHR)           g:insertVHR           = true; end
        end
    end
end



function->array int util:ConfigUpdateIndices(int iIndex, int iFlag)

    array int aArray;
    if (iFlag == g:updateCheck)
        if (g:checkAllRotations)
            aArray.push(util:RemoveRotation(iIndex));
        end
        if (g:checkAllRotations == false)
            if (g:checkOnlyRotations)
                aArray.push(iIndex.R, iIndex.N, iIndex.VH, iIndex.VHR);
            end
            if (g:checkOnlyRotations == false)
                if (g:checkV)  aArray.push(iIndex.V);  end
                if (g:checkH)  aArray.push(iIndex.H);  end
                if (g:checkVR) aArray.push(iIndex.VR); end
                if (g:checkHR) aArray.push(iIndex.HR); end
            end
            
            if (g:checkOnlyMirrors)
                aArray.push(iIndex.V, iIndex.H, iIndex.VR, iIndex.HR);
            end
            if (g:checkOnlyMirrors == false)
                if (g:checkR)   aArray.push(iIndex.R);   end
                if (g:checkN)   aArray.push(iIndex.N);   end
                if (g:checkVH)  aArray.push(iIndex.VH);  end
                if (g:checkVHR) aArray.push(iIndex.VHR); end
            end
        end
    end
    
    if (iFlag == g:updateInsert)
        if (g:insertAllRotations)
            aArray.push(util:RemoveRotation(iIndex), iIndex.V, iIndex.H, iIndex.R, iIndex.VH, iIndex.VR, iIndex.HR, iIndex.VHR);
        end
        if (g:insertAllRotations == false)
            if (g:insertOnlyRotations)
                aArray.push(util:RemoveRotation(iIndex), iIndex.R, iIndex.VH, iIndex.VHR);
            end
            if (g:insertOnlyRotations == false)
                if (g:insertV)  aArray.push(iIndex.V);  end
                if (g:insertH)  aArray.push(iIndex.H);  end
                if (g:insertVR) aArray.push(iIndex.VR); end
                if (g:insertHR) aArray.push(iIndex.HR); end
            end
            
            if (g:insertOnlyMirrors)
                aArray.push(iIndex.V, iIndex.H, iIndex.VR, iIndex.HR);
            end
            if (g:insertOnlyMirrors == false)
                if (g:insertN)   aArray.push(iIndex);     end
                if (g:insertR)   aArray.push(iIndex.R);   end
                if (g:insertVH)  aArray.push(iIndex.VH);  end
                if (g:insertVHR) aArray.push(iIndex.VHR); end
            end
        end
    end
    
    if (aArray.count == 0)
        aArray.push(iIndex);
    end
    return aArray;
end



function->array int util:ConfigUpdateIndices(array int aIndices, int iFlag)

    array int aArray;
    if (iFlag == g:updateCheck)
        if (g:checkAllRotations)
            for (i = 0 to aIndices.last)
                int iIndex = util:RemoveRotation(aIndices[i]);
                aArray.push(iIndex);
            end
        end
        if (g:checkAllRotations == false)
            if (g:checkOnlyRotations)
                for (i = 0 to aIndices.last)
                    int iIndex = aIndices[i];
                    aArray.push(iIndex.R, iIndex.N, iIndex.VH, iIndex.VHR);
                end
            end
            if (g:checkOnlyRotations == false)
                for (i = 0 to aIndices.last)
                    int iIndex = aIndices[i];
                    if (g:checkV)  aArray.push(iIndex.V);  end
                    if (g:checkH)  aArray.push(iIndex.H);  end
                    if (g:checkVR) aArray.push(iIndex.VR); end
                    if (g:checkHR) aArray.push(iIndex.HR); end
                end
            end
            
            if (g:checkOnlyMirrors)
                for (i = 0 to aIndices.last)
                    int iIndex = aIndices[i];
                    aArray.push(iIndex.V, iIndex.H, iIndex.VR, iIndex.HR);
                end
            end
            if (g:checkOnlyMirrors == false)
                for (i = 0 to aIndices.last)
                    int iIndex = aIndices[i];
                    if (g:checkR)   aArray.push(iIndex.R);   end
                    if (g:checkN)   aArray.push(iIndex.N);   end
                    if (g:checkVH)  aArray.push(iIndex.VH);  end
                    if (g:checkVHR) aArray.push(iIndex.VHR); end
                end
            end
        end
    end
    
    if (iFlag == g:updateInsert)
        if (g:insertAllRotations)
            for (i = 0 to aIndices.last)
                int iIndex = util:RemoveRotation(aIndices[i]);
                aArray.push(iIndex, iIndex.V, iIndex.H, iIndex.R, iIndex.VH, iIndex.VR, iIndex.HR, iIndex.VHR);
            end
        end
        if (g:insertAllRotations == false)
            if (g:insertOnlyRotations)
                for (i = 0 to aIndices.last)
                    int iIndex = util:RemoveRotation(aIndices[i]);
                    aArray.push(iIndex, iIndex.R, iIndex.VH, iIndex.VHR);
                end
            end
            if (g:insertOnlyRotations == false)
                for (i = 0 to aIndices.last)
                    int iIndex = aIndices[i];
                    if (g:insertV)  aArray.push(iIndex.V);  end
                    if (g:insertH)  aArray.push(iIndex.H);  end
                    if (g:insertVR) aArray.push(iIndex.VR); end
                    if (g:insertHR) aArray.push(iIndex.HR); end
                end
            end
            
            if (g:insertOnlyMirrors)
                for (i = 0 to aIndices.last)
                    int iIndex = aIndices[i];
                    aArray.push(iIndex.V, iIndex.H, iIndex.VR, iIndex.HR);
                end
            end
            if (g:insertOnlyMirrors == false)
                for (i = 0 to aIndices.last)
                    int iIndex = util:RemoveRotation(aIndices[i]);
                    if (g:insertN)   aArray.push(iIndex);     end
                    if (g:insertR)   aArray.push(iIndex.R);   end
                    if (g:insertVH)  aArray.push(iIndex.VH);  end
                    if (g:insertVHR) aArray.push(iIndex.VHR); end
                end
            end
        end
    end
    
    if (aArray.count == 0)
        aArray = aIndices;
    end
    return aArray;
end



function->array object util:ConfigUpdateObjects(object oObject, int iFlag)

    array object aArray;
    if (iFlag == g:updateCheck)
        if (g:checkAllRotations)
            aArray.push(oObject.V, oObject.H, oObject.R, oObject.N, oObject.VH, oObject.VR, oObject.HR, oObject.VHR);
        end
        if (g:checkAllRotations == false)
            if (g:checkOnlyRotations)
                aArray.push(oObject.R, oObject.N, oObject.VH, oObject.VHR);
            end
            if (g:checkOnlyRotations == false)
                if (g:checkV)  aArray.push(oObject.V);  end
                if (g:checkH)  aArray.push(oObject.H);  end
                if (g:checkVR) aArray.push(oObject.VR); end
                if (g:checkHR) aArray.push(oObject.HR); end
            end
            
            if (g:checkOnlyMirrors)
                aArray.push(oObject.V, oObject.H, oObject.VR, oObject.HR);
            end
            if (g:checkOnlyMirrors == false)
                if (g:checkR)   aArray.push(oObject.R);   end
                if (g:checkN)   aArray.push(oObject.N);   end
                if (g:checkVH)  aArray.push(oObject.VH);  end
                if (g:checkVHR) aArray.push(oObject.VHR); end
            end
        end
    end
    
    if (iFlag == g:updateInsert)
        if (g:insertAllRotations)
            aArray.push(oObject.V, oObject.H, oObject.R, oObject.N, oObject.VH, oObject.VR, oObject.HR, oObject.VHR);
        end
        if (g:insertAllRotations == false)
            if (g:insertOnlyRotations)
                aArray.push(oObject.R, oObject.N, oObject.VH, oObject.VHR);
            end
            if (g:insertOnlyRotations == false)
                if (g:insertV)  aArray.push(oObject.V);  end
                if (g:insertH)  aArray.push(oObject.H);  end
                if (g:insertVR) aArray.push(oObject.VR); end
                if (g:insertHR) aArray.push(oObject.HR); end
            end
            
            if (g:insertOnlyMirrors)
                aArray.push(oObject.V, oObject.H, oObject.VR, oObject.HR);
            end
            if (g:insertOnlyMirrors == false)
                if (g:insertR)   aArray.push(oObject.R);   end
                if (g:insertN)   aArray.push(oObject.N);   end
                if (g:insertVH)  aArray.push(oObject.VH);  end
                if (g:insertVHR) aArray.push(oObject.VHR); end
            end
        end
    end
    
    if (aArray.count == 0)
        aArray.push(oObject);
    end
    return aArray;
end



function->array object util:ConfigUpdateObjects(array object aObjects, int iFlag)

    array object aArray;
    if (iFlag == g:updateCheck)
        if (g:checkAllRotations)
            for (i = 0 to aObjects.last)
                object oObject = aObjects[i];
                aArray.push(oObject.V, oObject.H, oObject.R, oObject.N, oObject.VH, oObject.VR, oObject.HR, oObject.VHR);
            end
        end
        if (g:checkAllRotations == false)
            if (g:checkOnlyRotations)
                for (i = 0 to aObjects.last)
                    object oObject = aObjects[i];
                    aArray.push(oObject.R, oObject.N, oObject.VH, oObject.VHR);
                end
            end
            if (g:checkOnlyRotations == false)
                for (i = 0 to aObjects.last)
                    object oObject = aObjects[i];
                    if (g:checkV)  aArray.push(oObject.V);  end
                    if (g:checkH)  aArray.push(oObject.H);  end
                    if (g:checkVR) aArray.push(oObject.VR); end
                    if (g:checkHR) aArray.push(oObject.HR); end
                end
            end
            
            if (g:checkOnlyMirrors)
                for (i = 0 to aObjects.last)
                    object oObject = aObjects[i];
                    aArray.push(oObject.V, oObject.H, oObject.VR, oObject.HR);
                end
            end
            if (g:checkOnlyMirrors == false)
                for (i = 0 to aObjects.last)
                    object oObject = aObjects[i];
                    if (g:checkR)   aArray.push(oObject.R);   end
                    if (g:checkN)   aArray.push(oObject.N);   end
                    if (g:checkVH)  aArray.push(oObject.VH);  end
                    if (g:checkVHR) aArray.push(oObject.VHR); end
                end
            end
        end
    end
    
    if (iFlag == g:updateInsert)
        if (g:insertAllRotations)
            for (i = 0 to aObjects.last)
                object oObject = aObjects[i];
                aArray.push(oObject.V, oObject.H, oObject.R, oObject.N, oObject.VH, oObject.VR, oObject.HR, oObject.VHR);
            end
        end
        if (g:insertAllRotations == false)
            if (g:insertOnlyRotations)
                for (i = 0 to aObjects.last)
                    object oObject = aObjects[i];
                    aArray.push(oObject.R, oObject.N, oObject.VH, oObject.VHR);
                end
            end
            if (g:insertOnlyRotations == false)
                for (i = 0 to aObjects.last)
                    object oObject = aObjects[i];
                    if (g:insertV)  aArray.push(oObject.V);  end
                    if (g:insertH)  aArray.push(oObject.H);  end
                    if (g:insertVR) aArray.push(oObject.VR); end
                    if (g:insertHR) aArray.push(oObject.HR); end
                end
            end
            
            if (g:insertOnlyMirrors)
                for (i = 0 to aObjects.last)
                    object oObject = aObjects[i];
                    aArray.push(oObject.V, oObject.H, oObject.VR, oObject.HR);
                end
            end
            if (g:insertOnlyMirrors == false)
                for (i = 0 to aObjects.last)
                    object oObject = aObjects[i];
                    if (g:insertR)   aArray.push(oObject.R);   end
                    if (g:insertN)   aArray.push(oObject.N);   end
                    if (g:insertVH)  aArray.push(oObject.VH);  end
                    if (g:insertVHR) aArray.push(oObject.VHR); end
                end
            end
        end
    end
    
    if (aArray.count == 0)
        aArray = aObjects;
    end
    return aArray;
end



function->bool util:Is(int iIndex)

//
    if (s:debug)
        if (iIndex < -1 or iIndex > 255)
            error("util:Is(int iIndex) -> iIndex needs to be in range [-1-255].");
        end
    end
//

    insert.rule.pos.type = index;
    insert.rule.pos.index = iIndex;
        
    return true;
end



function->bool util:Is(array int aIndices)

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("util:Is(array int aIndices) -> aIndices was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < -1 or aIndices[i] > 255)
                error("util:Is(array int aIndices) -> values need to be in range [0-255].");
            end
        end
    end
//

    insert.rule.pos.type = index;
    for (i = 0 to aIndices.last)
        insert.rule.pos.index = aIndices[i];
    end
    return true;
end



function->bool util:IsNot(int iIndex)

//
    if (s:debug)
        if (iIndex < -1 or iIndex > 255)
            error("util:IsNot(int iIndex) -> iIndex needs to be in range [-1-255].");
        end
    end
//

    insert.rule.pos.type = notindex;
    insert.rule.pos.index = iIndex;
        
    return true;
end



function->bool util:IsNot(array int aIndices)

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("util:IsNot(array int aIndices) -> aIndices was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < -1 or aIndices[i] > 255)
                error("util:IsNot(array int aIndices) -> values need to be in range [0-255].");
            end
        end
    end
//

    insert.rule.pos.type = notindex;
    for (i = 0 to aIndices.last)
        insert.rule.pos.index = aIndices[i];
    end
    return true;
end



function->bool util:IsEmpty()

    insert.rule.pos.type = empty;
    return true;
end



function->bool util:IsFull()

    insert.rule.pos.type = full;
    return true;
end



function->bool util:IsOut()

    insert.rule.pos.type = index;
    insert.rule.pos.index = -1;
    return true;
end



function->bool util:IsNotOut()

    insert.rule.pos.type = notindex;
    insert.rule.pos.index = -1;
    return true;
end



function->null util:NewRule()
    
    insert.newrule;
end



function->null util:NewPosRule(coord cPos)

    insert.rule.pos = cPos;
end



function->null util:InsertIndex(int iIndex)

//
    if (s:debug)
        if (iIndex < 0 or iIndex > 255)
            error("util:InsertIndex(int iIndex) -> value needs to be in range [0-255].");
        end
    end
//

    insert.rule.index = iIndex;
end



function->null util:NoDefaultPosRule()

    insert.rule.nodefault;
end



function->null util:Chance(float fProbability)

    insert.rule.random = fProbability;
end



function->coord util:RelativePos(coord cAnchor, int iIndex)

    coord cPos = iIndex;
    
    bool hasV = cAnchor.rotate.V;
    bool hasH = cAnchor.rotate.H;
    bool hasR = cAnchor.rotate.R;
    
    if (hasV and hasH and hasR)
        return [cPos.y - cAnchor.y, cAnchor.x - cPos.x];
    end
    if (hasV and hasH)
        return [cAnchor.x - cPos.x, cAnchor.y - cPos.y];
    end
    if (hasV and hasR)
        return [cAnchor.y - cPos.y, cAnchor.x - cPos.x];
    end
    if (hasH and hasR)
        return [cPos.y - cAnchor.y, cPos.x - cAnchor.x];
    end
    if (hasV)
        return [cAnchor.x - cPos.x, cPos.y - cAnchor.y];
    end
    if (hasH)
        return [cPos.x - cAnchor.x, cAnchor.y - cPos.y];
    end
    if (hasR)
        return [cAnchor.y - cPos.y, cPos.x - cAnchor.x];
    end
    
    return [cPos.x - cAnchor.x, cPos.y - cAnchor.y];
end



function->int util:Min(array int aValues)

    if (aValues.count == 0)
        return g:intMin;
    end
    
    int iResult = g:intMax;
    for (i = 0 to aValues.last)        
        if (aValues[i] < iResult)
            iResult = aValues[i];
        end
    end
    return iResult;
end



function->int util:Max(array int aValues)

    if (aValues.count == 0)
        return g:intMax;
    end
    
    int iResult = g:intMin;
    for (i = 0 to aValues.last)        
        if (aValues[i] > iResult)
            iResult = aValues[i];
        end
    end
    return iResult;
end



function->array int util:Rect(object oObject)

//
    if (s:debug)
        if (oObject.count == 0)
            error("util:Rect(object oObject) -> oObject cannot be empty.");
        end
    end
//
    
    array int aX;
    array int aY;
    
    coord cAnchor = oObject.anchor;
    for (i = 0 to oObject.last)
        coord cRelativePos = util:RelativePos(cAnchor, oObject[i]);
        
        aX.push(cRelativePos.x);
        aY.push(cRelativePos.y);
    end
    
    array int aResult;
    aResult.push(0, util:Max(aX), util:Max(aY), util:Min(aX)); // top, right, bottom, left
    
    return aResult;
end



function->coord util:Size(object oObject)

//
    if (s:debug)
        if (oObject.count == 0)
            error("util:Size(object oObject) -> oObject cannot be empty.");
        end
    end
//

    array int aRect = util:Rect(oObject);    
    return [aRect[1] - aRect[3] + 1, aRect[2] - aRect[0] + 1];
end





///////////////////////////////////////
// general functions
///////////////////////////////////////
/******************************************************************************

*/
function->null AutoMapper(string sName)

    insert.automapper = sName;
end



function->null NewRun()

    insert.newrun = 1;
end



function->null NewRun(int iCopies)

//
    if (s:debug)
        if (iCopies < 1)
            error("NewRun(int iCopies) -> value needs to be greater than 0.");
        end
    end
//

    insert.newrun = iCopies;
end



function->null OverrideLayer()

    insert.nocopy;
end



function->array coord PosRange(range rX, range rY)

    array int aX = util:ArrayInt(rX);
    array int aY = util:ArrayInt(rY);

    array coord aResult;
    for (i = 0 to aX.last)
        for (j = 0 to aY.last)
            aResult.push([aX[i], aY[j]]);
        end
    end
    return aResult;
end



function->array coord PosRange(range rX, int iY)

    array int aX = util:ArrayInt(rX);

    array coord aResult;
    for (i = 0 to aX.last)
        aResult.push([aX[i], iY]);
    end
    return aResult;
end



function->array coord PosRange(int iX, range rY)

    array int aY = util:ArrayInt(rY);

    array coord aResult;
    for (i = 0 to aY.last)
        aResult.push([iX, aY[i]]);
    end
    return aResult;
end



function->object Indices(array int aIndices)

//
    if (s:debug)
        if (aIndices.count == 0)
            error("Indices(array int aIndices) -> aIndices was empty, object would be invalid.");
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < 0 or aIndices[i] > 255)
                error("Indices(array int aIndices) -> values need to be in range [0-255].");
            end
        end
    end
//
    
    object oResult = aIndices;
    return oResult.N;
end



function->object Rect(int iTopLeft, int iBottomRight)

//
    if (s:debug)
        if (iTopLeft < 0 or iTopLeft > 255)
            error("Rect(int iTopLeft, int iBottomRight) -> iTopLeft needs to be in range [0-255].");
        end
        
        if (iBottomRight < 0 or iBottomRight > 255)
            error("Rect(int iTopLeft, int iBottomRight) -> iBottomRight needs to be in range [0-255].");
        end
    end
//

    coord cTopLeft = iTopLeft;
    coord cBottomRight = iBottomRight;
    
    array int aResult;
    for (x = cTopLeft.x to cBottomRight.x)
        for (y = cTopLeft.y to cBottomRight.y)
            aResult.push([x, y]);
        end
    end
    return Indices(aResult);
end



function->int Negate(int iValue)

    return iValue * -1;
end



function->coord Negate(coord cValue)

    return [cValue.x * -1, cValue.y * -1];
end



///////////////////////////////////////
//
bool g:runInsertTests = false;
bool g:callInsertNested = true;
bool g:callInsertConfig = true;

bool g:runIndexAtNewruleCheck = false;
bool g:createNewruleInsert = true;
/******************************************************************************

*/
function->null internal:InsertResetFlags()

    g:runInsertTests = false;
    g:callInsertConfig = true;

    g:runIndexAtNewruleCheck = false;
    g:createNewruleInsert = true;
end



function->null Insert(array int aIndices) 
    nested(
        Config,
        At,
        NoDefaultPosRule, Chance, If
    )

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("Insert(array int aIndices) -> aIndices was empty, function had no effect.");
            return;
        end
        
        for (i = 0 to aIndices.last)
            if (aIndices[i] < 0 or aIndices[i] > 255)
                error("Insert(array int aIndices) -> values need to be in range [0-255].");
            end
        end
    end
//    
    
    g:runIndexAtNewruleCheck = true;
    util:ResetSettings(g:resetInsert);
    invoke(nested);
    g:runIndexAtNewruleCheck = false;
    
    g:runInsertTests = true;

    array int aArray = util:ConfigUpdateIndices(aIndices, g:updateInsert);
    for (i = 0 to aArray.last)
        g:vInsertIndex = aArray[i];
        
        if (g:createNewruleInsert)
            insert.newrule;
            util:InsertIndex(g:vInsertIndex);
        end
        
        invoke(nested);
    end
    internal:InsertResetFlags();
end



nested function->null Insert.Config(array int aSettings)

    if (g:callInsertConfig and g:callInsertNested)
        util:ConfigUpdate(aSettings, g:updateInsert);
        
        g:callInsertConfig = false;
    end
end



nested function->null Insert.At(coord cPos)
    
    if (g:runInsertTests == false)
        g:callInsertNested = false;
        return;
    end
    
//
    if (s:debug)
        if (cPos.x < 0)
            warning("Insert.At(coord cPos) -> cPos.x was negative, function had no effect.");
            return;
        end
        if (cPos.y < 0)
            warning("Insert.At(coord cPos) -> cPos.y was negative, function had no effect.");
            return;
        end
    end
//

    coord cPosNegated = Negate(cPos);

    insert.rule.pos = cPosNegated;
    util:IsNotOut();
    insert.rule.pos = [cPosNegated.x - 1, 0];
    util:IsOut();
    insert.rule.pos = [0, cPosNegated.y - 1];
    util:IsOut();
    util:NoDefaultPosRule();
end



nested function->null Insert.NoDefaultPosRule()

    if (g:runInsertTests and g:callInsertNested)
        util:NoDefaultPosRule();
    end
end



nested function->null Insert.Chance(float fProbability)

    if (g:runInsertTests and g:callInsertNested)
        util:Chance(fProbability);
    end
end



nested function->null Insert.If(array bool bTests)
end



///////////////////////////////////////
//
coord g:posIndexAt = [0, 0];

bool g:runIndexAtTests = false;
bool g:callIndexAtConfig = true;

bool g:callIndexAtIs               = false;
bool g:callIndexAtIsNot            = false;
bool g:callIndexAtIsEmpty          = false;
bool g:callIndexAtIsEmptyAt        = false;
bool g:callIndexAtIsFull           = false;
bool g:callIndexAtIsFullAt         = false;
bool g:callIndexAtIsOut            = false;
bool g:callIndexAtIsNotOut         = false;
bool g:callIndexAtIsEdge           = false;
bool g:callIndexAtIsNotEdge        = false;
bool g:callIndexAtIsNotNextTo      = false;
bool g:callIndexAtIsWall           = false;
bool g:callIndexAtIsOuterCorner    = false;
bool g:callIndexAtIsInnerCorner    = false;
bool g:callIndexAtHasSpaceFor      = false;
bool g:callIndexAtIsNotOverlapping = false;
bool g:callIndexAtIsNextTo         = false;
bool g:callIndexAtIsOverlapping    = false;

bool g:updateArgIndexAtIs = true;
array int g:argIndexAtIs;

bool g:updateArgIndexAtIsNot = true;
array int g:argIndexAtIsNot;

bool g:updateArgIndexAtIsNextTo = true;
array int g:argIndexAtIsNextTo;

bool g:updateArgIndexAtIsNotNextTo = true;
array int g:argIndexAtIsNotNextTo;

bool g:updateArgIndexAtIsNotOverlapping = true;
array object g:argIndexAtIsNotOverlapping;

array int g:argIndexAtIsEmptyAt;
array int g:argIndexAtIsFullAt;
array int g:argIndexAtIsNotEdge;
array int g:argIndexAtIsWall;
array int g:argIndexAtIsOuterCorner;
array int g:argIndexAtIsInnerCorner;
object g:argIndexAtHasSpaceFor;

int g:argIndexAtIsEdge = 0;

int g:borderTop         = 1;
int g:borderRight       = 1;
int g:borderBottom      = 1;
int g:borderLeft        = 1;
int g:borderTopLeft     = 1;
int g:borderTopRight    = 1;
int g:borderBottomLeft  = 1;
int g:borderBottomRight = 1;

int top         = 100;
int right       = 101;
int bottom      = 102;
int left        = 103;
int topLeft     = 104;
int topRight    = 105;
int bottomLeft  = 106;
int bottomRight = 107;
/******************************************************************************

*/
function->null internal:IndexAtResetFlags()

    g:runIndexAtTests = false;
    g:callIndexAtConfig = true;

    g:callIndexAtIs               = false;
    g:callIndexAtIsNot            = false;
    g:callIndexAtIsEmpty          = false;
    g:callIndexAtIsEmptyAt        = false;
    g:callIndexAtIsFull           = false;
    g:callIndexAtIsFullAt         = false;
    g:callIndexAtIsOut            = false;
    g:callIndexAtIsNotOut         = false;
    g:callIndexAtIsEdge           = false;
    g:callIndexAtIsNotEdge        = false;
    g:callIndexAtIsNextTo         = false;
    g:callIndexAtIsNotNextTo      = false;
    g:callIndexAtIsWall           = false;
    g:callIndexAtIsOuterCorner    = false;
    g:callIndexAtIsInnerCorner    = false;
    g:callIndexAtHasSpaceFor      = false;
    g:callIndexAtIsNotOverlapping = false;
    g:callIndexAtIsOverlapping    = false;

    g:updateArgIndexAtIs               = true;
    g:updateArgIndexAtIsNot            = true;
    g:updateArgIndexAtIsNextTo         = true;
    g:updateArgIndexAtIsNotNextTo      = true;
    g:updateArgIndexAtIsNotOverlapping = true;
end



function->null internal:ResetBorderFlags()
    
    g:borderTop         = 1;
    g:borderRight       = 1;
    g:borderBottom      = 1;
    g:borderLeft        = 1;
    g:borderTopLeft     = 1;
    g:borderTopRight    = 1;
    g:borderBottomLeft  = 1;
    g:borderBottomRight = 1;
end



function->null internal:BorderRule()
    
    if (g:borderTop == 1 and g:borderRight == 1 and g:borderBottom == 1 and g:borderLeft == 1 and g:borderTopLeft == 1 and g:borderTopRight == 1 and g:borderBottomLeft == 1 and g:borderBottomRight == 1)
        return;
    end
    
    //insert.rule.pos.type = full;
    
    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;
    
    if (g:borderTop         == 0) insert.rule.pos = [iX    , iY - 1]; insert.rule.pos.type = empty; end
    if (g:borderRight       == 0) insert.rule.pos = [iX + 1, iY    ]; insert.rule.pos.type = empty; end
    if (g:borderBottom      == 0) insert.rule.pos = [iX    , iY + 1]; insert.rule.pos.type = empty; end
    if (g:borderLeft        == 0) insert.rule.pos = [iX - 1, iY    ]; insert.rule.pos.type = empty; end
    if (g:borderTopLeft     == 0) insert.rule.pos = [iX - 1, iY - 1]; insert.rule.pos.type = empty; end
    if (g:borderTopRight    == 0) insert.rule.pos = [iX + 1, iY - 1]; insert.rule.pos.type = empty; end
    if (g:borderBottomLeft  == 0) insert.rule.pos = [iX - 1, iY + 1]; insert.rule.pos.type = empty; end
    if (g:borderBottomRight == 0) insert.rule.pos = [iX + 1, iY + 1]; insert.rule.pos.type = empty; end
    
    if (g:borderTop         == 1) insert.rule.pos = [iX    , iY - 1]; insert.rule.pos.type = full; end
    if (g:borderRight       == 1) insert.rule.pos = [iX + 1, iY    ]; insert.rule.pos.type = full; end
    if (g:borderBottom      == 1) insert.rule.pos = [iX    , iY + 1]; insert.rule.pos.type = full; end
    if (g:borderLeft        == 1) insert.rule.pos = [iX - 1, iY    ]; insert.rule.pos.type = full; end
    if (g:borderTopLeft     == 1) insert.rule.pos = [iX - 1, iY - 1]; insert.rule.pos.type = full; end
    if (g:borderTopRight    == 1) insert.rule.pos = [iX + 1, iY - 1]; insert.rule.pos.type = full; end
    if (g:borderBottomLeft  == 1) insert.rule.pos = [iX - 1, iY + 1]; insert.rule.pos.type = full; end
    if (g:borderBottomRight == 1) insert.rule.pos = [iX + 1, iY + 1]; insert.rule.pos.type = full; end
end



function->bool IndexAt(array coord aCoords) 
    nested(
        Config,
        Is, IsNot, IsEmpty, IsEmptyAt, IsFull, IsFullAt, IsOut, IsNotOut,
        IsEdge, IsNotEdge,
        IsNextTo, IsNotNextTo,
        IsWall, IsOuterCorner, IsInnerCorner,
        HasSpaceFor,
        IsNotOverlapping, IsOverlapping
    )
    
//
    if (s:debug)
        if (aCoords.count == 0)
            warning("IndexAt(array coord aCoords) -> aCoords was empty, function had no effect.");
            return false;
        end
    end
//

    if (g:runIndexAtNewruleCheck)
        invoke(nested);
        return true;
    end
    if (g:runInsertTests == false)
        return false;
    end

    util:ResetSettings(g:resetCheck);
    invoke(nested);
    
    g:runInsertTests = true;
    g:runIndexAtTests = true;
    
    for (i = 0 to aCoords.last)
        if (g:callIndexAtIsNextTo == false and g:callIndexAtIsOverlapping == false)
            insert.rule.pos = aCoords[i];
        end
        
        g:posIndexAt = aCoords[i];
        invoke(nested);
        
        internal:BorderRule();
        internal:ResetBorderFlags();
    end
    
    internal:IndexAtResetFlags();
    return true;
end



nested function->bool IndexAt.Config(array int aSettings)

    if (g:runIndexAtNewruleCheck)
        return false;
    end
    
    if (g:callIndexAtConfig)
        util:ConfigUpdate(aSettings, g:updateCheck);
        
        g:callIndexAtConfig = false;
    end
    return true;
end



function->null internal:IndexAtIs()
    
    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    insert.rule.pos = [iX, iY];
    insert.rule.pos.type = index;
    for (i = 0 to g:argIndexAtIs.last)
        insert.rule.pos.index = g:argIndexAtIs[i];
    end
end



nested function->bool IndexAt.Is(array int aIndices)

    if (g:runIndexAtNewruleCheck)
        return false;
    end

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("IndexAt.Is(array int aIndices) -> aIndices was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < -1 or aIndices[i] > 255)
                error("IndexAt.Is(array int aIndices) -> values need to be in range [-1-255].");
            end
        end
    end
//
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIs = true;
        
        g:argIndexAtIs = aIndices;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end
    
    if (g:updateArgIndexAtIs and g:callIndexAtIs)
        g:argIndexAtIs = util:ConfigUpdateIndices(g:argIndexAtIs, g:updateCheck);
        g:updateArgIndexAtIs = false;
    end
    
    internal:IndexAtIs();
    return true;
end



function->null internal:IndexAtIsNot()
    
    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    insert.rule.pos = [iX, iY];
    insert.rule.pos.type = notindex;
    for (i = 0 to g:argIndexAtIsNot.last)
        insert.rule.pos.index = g:argIndexAtIsNot[i];
    end
end



nested function->bool IndexAt.IsNot(array int aIndices)

    if (g:runIndexAtNewruleCheck)
        return false;
    end

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("IndexAt.IsNot(array int aIndices) -> aIndices was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < -1 or aIndices[i] > 255)
                error("IndexAt.IsNot(array int aIndices) -> values need to be in range [-1-255].");
            end
        end
    end
//
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsNot = true;
        
        g:argIndexAtIsNot = aIndices;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end
    
    if (g:updateArgIndexAtIsNot and g:callIndexAtIsNot)
        g:argIndexAtIsNot = util:ConfigUpdateIndices(g:argIndexAtIsNot, g:updateCheck);
        g:updateArgIndexAtIsNot = false;
    end
    
    internal:IndexAtIsNot();
    return true;
end



function->null internal:IndexAtIsEmpty()

    insert.rule.pos.type = empty;
end



nested function->bool IndexAt.IsEmpty()

    if (g:runIndexAtNewruleCheck)
        return false;
    end
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsEmpty = true;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end
    
    internal:IndexAtIsEmpty();
    return true;
end



function->null internal:IndexAtIsEmptyAt()

    array int aOrientations = g:argIndexAtIsEmptyAt;
    
    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;
    
    for (i = 0 to aOrientations.last)
        int iOrientation = aOrientations[i];
    
        if (iOrientation == top)
            insert.rule.pos = [iX, iY - 1];
            insert.rule.pos.type = empty;
        end
        if (iOrientation == right)
            insert.rule.pos = [iX + 1, iY];
            insert.rule.pos.type = empty;
        end
        if (iOrientation == bottom)
            insert.rule.pos = [iX, iY + 1];
            insert.rule.pos.type = empty;
        end
        if (iOrientation == left)
            insert.rule.pos = [iX - 1, iY];
            insert.rule.pos.type = empty;
        end
        if (iOrientation == topLeft)
            insert.rule.pos = [iX - 1, iY - 1];
            insert.rule.pos.type = empty;
        end
        if (iOrientation == topRight)
            insert.rule.pos = [iX + 1, iY - 1];
            insert.rule.pos.type = empty;
        end
        if (iOrientation == bottomLeft)
            insert.rule.pos = [iX - 1, iY + 1];
            insert.rule.pos.type = empty;
        end
        if (iOrientation == bottomRight)
            insert.rule.pos = [iX + 1, iY + 1];
            insert.rule.pos.type = empty;
        end
    end
end



nested function->bool IndexAt.IsEmptyAt(array int aOrientations)

    if (g:runIndexAtNewruleCheck)
        return false;
    end
    
//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IndexAt.IsEmptyAt(array int aOrientations) -> aOrientations was empty, function had no effect.");
            return false;
        end
    end
//
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsEmptyAt = true;
        
        g:argIndexAtIsEmptyAt = aOrientations;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end

    internal:IndexAtIsEmptyAt();
    return true;
end



function->null internal:IndexAtIsFull()

    insert.rule.pos.type = full;
end



nested function->bool IndexAt.IsFull()

    if (g:runIndexAtNewruleCheck)
        return false;
    end
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsFull = true;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end
    
    internal:IndexAtIsFull();
    return true;
end



function->null internal:IndexAtIsFullAt()

    array int aOrientations = g:argIndexAtIsFullAt;

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;
    
    for (i = 0 to aOrientations.last)
        int iOrientation = aOrientations[i];
    
        if (iOrientation == top)
            insert.rule.pos = [iX, iY - 1];
            insert.rule.pos.type = full;
        end
        if (iOrientation == right)
            insert.rule.pos = [iX + 1, iY];
            insert.rule.pos.type = full;
        end
        if (iOrientation == bottom)
            insert.rule.pos = [iX, iY + 1];
            insert.rule.pos.type = full;
        end
        if (iOrientation == left)
            insert.rule.pos = [iX - 1, iY];
            insert.rule.pos.type = full;
        end
        if (iOrientation == topLeft)
            insert.rule.pos = [iX - 1, iY - 1];
            insert.rule.pos.type = full;
        end
        if (iOrientation == topRight)
            insert.rule.pos = [iX + 1, iY - 1];
            insert.rule.pos.type = full;
        end
        if (iOrientation == bottomLeft)
            insert.rule.pos = [iX - 1, iY + 1];
            insert.rule.pos.type = full;
        end
        if (iOrientation == bottomRight)
            insert.rule.pos = [iX + 1, iY + 1];
            insert.rule.pos.type = full;
        end
    end
end



nested function->bool IndexAt.IsFullAt(array int aOrientations)

    if (g:runIndexAtNewruleCheck)
        return false;
    end
    
//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IndexAt.IsFullAt(array int aOrientations) -> aOrientations was empty, function had no effect.");
            return false;
        end
    end
//
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsFullAt = true;
        
        g:argIndexAtIsFullAt = aOrientations;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end

    internal:IndexAtIsFullAt();
    return true;
end



function->null internal:IndexAtIsOut()

    insert.rule.pos.type = index;
    insert.rule.pos.index = -1;
end



nested function->bool IndexAt.IsOut()

    if (g:runIndexAtNewruleCheck)
        return false;
    end
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsOut = true;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end
    
    internal:IndexAtIsOut();
    return true;
end



function->null internal:IndexAtIsNotOut()

    insert.rule.pos.type = notindex;
    insert.rule.pos.index = -1;
end



nested function->bool IndexAt.IsNotOut()

    if (g:runIndexAtNewruleCheck)
        return false;
    end
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsNotOut = true;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end
    
    internal:IndexAtIsNotOut();
    return true;
end



function->null internal:IndexAtIsEdge()

    int iOrientation = g:argIndexAtIsEdge;
    
    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;
    
    if (iOrientation == top)
        insert.rule.pos = [iX, iY - 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
    end
    if (iOrientation == right)
        insert.rule.pos = [iX + 1, iY];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
    end
    if (iOrientation == bottom)
        insert.rule.pos = [iX, iY + 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
    end
    if (iOrientation == left)
        insert.rule.pos = [iX - 1, iY];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
    end
    if (iOrientation == topLeft)
        insert.rule.pos = [iX, iY - 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        insert.rule.pos = [iX - 1, iY];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
    end
    if (iOrientation == topRight)
        insert.rule.pos = [iX, iY - 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        insert.rule.pos = [iX + 1, iY];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
    end
    if (iOrientation == bottomLeft)
        insert.rule.pos = [iX, iY + 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        insert.rule.pos = [iX - 1, iY];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
    end
    if (iOrientation == bottomRight)
        insert.rule.pos = [iX, iY + 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        insert.rule.pos = [iX + 1, iY];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
    end
end



nested function->bool IndexAt.IsEdge(int iOrientation)

    if (g:runIndexAtNewruleCheck)
        return false;
    end
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsEdge = true;
        
        g:argIndexAtIsEdge = iOrientation;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end

    internal:IndexAtIsEdge();
    return true;
end



function->null internal:IndexAtIsNotEdge()

    array int aOrientations = g:argIndexAtIsNotEdge;

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    for (i = 0 to aOrientations.last)    
        if (aOrientations[i] == top)
            insert.rule.pos = [iX, iY - 1];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (aOrientations[i] == right)
            insert.rule.pos = [iX + 1, iY];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (aOrientations[i] == bottom)
            insert.rule.pos = [iX, iY + 1];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (aOrientations[i] == left)
            insert.rule.pos = [iX - 1, iY];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
    end
end



nested function->bool IndexAt.IsNotEdge(array int aOrientations)

    if (g:runIndexAtNewruleCheck)
        return false;
    end

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IndexAt.IsNotEdge(array int aOrientations) -> aOrientations was empty, function had no effect.");
            return false;
        end
    end
//
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsNotEdge = true;
        
        g:argIndexAtIsNotEdge = aOrientations;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end
    
    internal:IndexAtIsNotEdge();
    return true;
end



function->null internal:IndexAtIsWall()

    array int aOrientations = g:argIndexAtIsWall;

    if (aOrientations.has(top))
        g:borderTop = 0;
        g:borderTopLeft = -1;
        g:borderTopRight = -1;
    end
    if (aOrientations.has(right))
        g:borderRight = 0;
        g:borderTopRight = -1;
        g:borderBottomRight = -1;
    end
    if (aOrientations.has(bottom))
        g:borderBottom = 0;
        g:borderBottomLeft = -1;
        g:borderBottomRight = -1;
    end
    if (aOrientations.has(left))
        g:borderLeft = 0;
        g:borderTopLeft = -1;
        g:borderBottomLeft = -1;
    end
end



nested function->bool IndexAt.IsWall(array int aOrientations)

    if (g:runIndexAtNewruleCheck)
        return false;
    end

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IndexAt.IsWall(array int aOrientations) -> aOrientations was empty, function had no effect.");
            return false;
        end
    end
//
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsWall = true;
        
        g:argIndexAtIsWall = aOrientations;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end

    internal:IndexAtIsWall();
    return true;
end



function->null internal:IndexAtIsOuterCorner()

    array int aOrientations = g:argIndexAtIsOuterCorner;
    
    if (aOrientations.has(topLeft))
        g:borderTop = 0;
        g:borderLeft = 0;
        g:borderTopLeft = -1;
        g:borderTopRight = -1;
        g:borderBottomLeft = -1;
    end
    if (aOrientations.has(topRight))
        g:borderTop = 0;
        g:borderRight = 0;
        g:borderTopLeft = -1;
        g:borderTopRight = -1;
        g:borderBottomRight = -1;
    end
    if (aOrientations.has(bottomLeft))
        g:borderBottom = 0;
        g:borderLeft = 0;
        g:borderTopLeft = -1;
        g:borderBottomLeft = -1;
        g:borderBottomRight = -1;
    end
    if (aOrientations.has(bottomRight))
        g:borderBottom = 0;
        g:borderRight = 0;
        g:borderTopRight = -1;
        g:borderBottomLeft = -1;
        g:borderBottomRight = -1;
    end
end



nested function->bool IndexAt.IsOuterCorner(array int aOrientations)

    if (g:runIndexAtNewruleCheck)
        return false;
    end

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IndexAt.IsOuterCorner(array int aOrientations) -> aOrientations was empty, function had no effect.");
            return false;
        end
    end
//
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsOuterCorner = true;
        
        g:argIndexAtIsOuterCorner = aOrientations;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end

    internal:IndexAtIsOuterCorner();
    return true;
end



function->null internal:IndexAtIsInnerCorner()

    array int aOrientations = g:argIndexAtIsInnerCorner;
    
    if (aOrientations.has(topLeft))
        g:borderTopLeft = 0;
    end
    if (aOrientations.has(topRight))
        g:borderTopRight = 0;
    end
    if (aOrientations.has(bottomLeft))
        g:borderBottomLeft = 0;
    end
    if (aOrientations.has(bottomRight))
        g:borderBottomRight = 0;
    end
end



nested function->bool IndexAt.IsInnerCorner(array int aOrientations)

    if (g:runIndexAtNewruleCheck)
        return false;
    end

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IndexAt.IsInnerCorner(array int aOrientations) -> aOrientations was empty, function had no effect.");
            return false;
        end
    end
//
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsInnerCorner = true;
        
        g:argIndexAtIsInnerCorner = aOrientations;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end
    
    internal:IndexAtIsInnerCorner();
    return true;
end



function->null internal:IndexAtHasSpaceFor()
    
    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;
    
    for (i = 0 to g:argIndexAtHasSpaceFor.last)
        coord cRelativePos = util:RelativePos(g:argIndexAtHasSpaceFor.anchor, g:argIndexAtHasSpaceFor[i]);
    
        insert.rule.pos = [cRelativePos.x + iX, cRelativePos.y + iY];
        insert.rule.pos.type = full;
    end
end



nested function->bool IndexAt.HasSpaceFor(object oObject)
    
    if (g:runIndexAtNewruleCheck)
        return false;
    end

//
    if (s:debug)
        if (oObject.count == 0)
            warning("IndexAt.HasSpaceFor(object oObject) -> oObject was empty, function had no effect.");
            return false;
        end
    end
//
    
    if (g:runIndexAtTests == false)
        g:callIndexAtHasSpaceFor = true;
        
        g:argIndexAtHasSpaceFor = oObject;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end

    internal:IndexAtHasSpaceFor();
    return true;
end



function->null internal:IndexAtIsNotOverlapping()
    
    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    for (i = 0 to g:argIndexAtIsNotOverlapping.last)
        coord cAnchor = g:argIndexAtIsNotOverlapping[i].anchor;
        
        for (j = 0 to g:argIndexAtIsNotOverlapping[i].last)
            coord cRelativePos = util:RelativePos(cAnchor, g:argIndexAtIsNotOverlapping[i][j]);
            
            insert.rule.pos = [iX + cRelativePos.x * -1, iY + cRelativePos.y * -1];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = cAnchor;
        end
    end
    insert.nocopy;
end



nested function->bool IndexAt.IsNotOverlapping(array object aObjects)
    
    if (g:runIndexAtNewruleCheck)
        return false;
    end

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("IndexAt.IsNotOverlapping(array object aObjects) -> aObjects was empty, function had no effect.");
            return false;
        end
    end
//
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsNotOverlapping = true;
        
        g:argIndexAtIsNotOverlapping = aObjects;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end
    
    if (g:updateArgIndexAtIsNotOverlapping and g:callIndexAtIsNotOverlapping)
        g:argIndexAtIsNotOverlapping = util:ConfigUpdateObjects(g:argIndexAtIsNotOverlapping, g:updateCheck);
        g:updateArgIndexAtIsNotOverlapping = false;
    end
    
    internal:IndexAtIsNotOverlapping();
    return true;
end



function->null internal:IndexAtIsNotNextTo()

    for (i = 0 to g:argIndexAtIsNotNextTo.last)
        int iIndex = g:argIndexAtIsNotNextTo[i];
    
        insert.rule.pos = [-1, 0];
        util:IsNot(iIndex);
        
        insert.rule.pos = [0, -1];
        util:IsNot(iIndex);
        
        insert.rule.pos = [1, 0];
        util:IsNot(iIndex);
        
        insert.rule.pos = [0, 1];
        util:IsNot(iIndex);
    end
end



nested function->bool IndexAt.IsNotNextTo(array int aIndices)

    if (g:runIndexAtNewruleCheck)
        return false;
    end

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("IndexAt.IsNotNextTo(array int aIndices) -> aIndices was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < -1 or aIndices[i] > 255)
                error("IndexAt.IsNotNextTo(array int aIndices) -> values need to be in range [-1-255].");
            end
        end
    end
//
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsNotNextTo = true;
        
        g:argIndexAtIsNotNextTo = aIndices;
        return false;
    end
    if (g:callIndexAtIsOverlapping)
        return false;
    end
    
    if (g:updateArgIndexAtIsNotNextTo and g:callIndexAtIsNotNextTo)
        g:argIndexAtIsNotNextTo = util:ConfigUpdateIndices(g:argIndexAtIsNotNextTo, g:updateCheck);
        g:updateArgIndexAtIsNotNextTo = false;
    end
    
    internal:IndexAtIsNotNextTo();
    return true;
end



function->null internal:IndexAtExecuteCalls()

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;
    
    if (g:callIndexAtIs)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIs();
    end
    if (g:callIndexAtIsNot)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsNot();
    end
    if (g:callIndexAtIsEmpty)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsEmpty();
    end
    if (g:callIndexAtIsEmptyAt)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsEmptyAt();
    end
    if (g:callIndexAtIsFull)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsFull();
    end
    if (g:callIndexAtIsFullAt)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsFullAt();
    end
    if (g:callIndexAtIsOut)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsOut();
    end
    if (g:callIndexAtIsNotOut)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsNotOut();
    end
    if (g:callIndexAtIsEdge)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsEdge();
    end
    if (g:callIndexAtIsNotEdge)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsNotEdge();
    end
    if (g:callIndexAtIsNotNextTo)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsNotNextTo();
    end
    if (g:callIndexAtIsWall)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsWall();
    end
    if (g:callIndexAtIsOuterCorner)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsOuterCorner();
    end
    if (g:callIndexAtIsInnerCorner)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsInnerCorner();
    end
    if (g:callIndexAtHasSpaceFor)
        insert.rule.pos = [iX, iY];
        internal:IndexAtHasSpaceFor();
    end
    if (g:callIndexAtIsNotOverlapping)
        insert.rule.pos = [iX, iY];
        internal:IndexAtIsNotOverlapping();
    end
end



function->null internal:IndexAtIsNextTo()

    for (i = 0 to g:argIndexAtIsNextTo.last)
        int iIndex = g:argIndexAtIsNextTo[i];
    
        insert.newrule;
        util:InsertIndex(g:vInsertIndex);
        insert.rule.pos = [-1, 0];
        util:Is(iIndex);
        
        internal:IndexAtExecuteCalls();
        
        insert.newrule;
        util:InsertIndex(g:vInsertIndex);
        insert.rule.pos = [0, -1];
        util:Is(iIndex);
        
        internal:IndexAtExecuteCalls();
        
        insert.newrule;
        util:InsertIndex(g:vInsertIndex);
        insert.rule.pos = [1, 0];
        util:Is(iIndex);
        
        internal:IndexAtExecuteCalls();
        
        insert.newrule;
        util:InsertIndex(g:vInsertIndex);
        insert.rule.pos = [0, 1];
        util:Is(iIndex);
        
        internal:IndexAtExecuteCalls();
    end
end



nested function->bool IndexAt.IsNextTo(array int aIndices)

    if (g:runIndexAtNewruleCheck)
        g:createNewruleInsert = false;
        return false;
    end

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("IndexAt.IsNextTo(array int aIndices) -> aIndices was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < -1 or aIndices[i] > 255)
                error("IndexAt.IsNextTo(array int aIndices) -> values need to be in range [-1-255].");
            end
        end
    end
//
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsNextTo = true;
        
        g:argIndexAtIsNextTo = aIndices;
        return false;
    end
    
    if (g:updateArgIndexAtIsNextTo and g:callIndexAtIsNextTo)
        g:argIndexAtIsNextTo = util:ConfigUpdateIndices(g:argIndexAtIsNextTo, g:updateCheck);
        g:updateArgIndexAtIsNextTo = false;
    end
    
    internal:IndexAtIsNextTo();
    return true;
end



nested function->bool IndexAt.IsOverlapping(array object aObjects)

    if (g:runIndexAtNewruleCheck)
        g:createNewruleInsert = false;
        return false;
    end
    
    if (g:runIndexAtTests == false)
        g:callIndexAtIsOverlapping = true;
        return false;
    end
    
//
    if (s:debug)
        if (aObjects.count == 0)
            warning("IndexAt.IsOverlapping(array object aObjects) -> aObjects was empty, function had no effect.");
            return false;
        end
    end
//

    aObjects = util:ConfigUpdateObjects(aObjects, g:updateCheck);
    
    if (g:updateArgIndexAtIs and g:callIndexAtIs)
        g:argIndexAtIs = util:ConfigUpdateIndices(g:argIndexAtIs, g:updateCheck);
        g:updateArgIndexAtIs = false;
    end
    if (g:updateArgIndexAtIsNot and g:callIndexAtIsNot)
        g:argIndexAtIsNot = util:ConfigUpdateIndices(g:argIndexAtIsNot, g:updateCheck);
        g:updateArgIndexAtIsNot = false;
    end
    if (g:updateArgIndexAtIsNotNextTo and g:callIndexAtIsNotNextTo)
        g:argIndexAtIsNotNextTo = util:ConfigUpdateIndices(g:argIndexAtIsNotNextTo, g:updateCheck);
        g:updateArgIndexAtIsNotNextTo = false;
    end
    if (g:updateArgIndexAtIsNotOverlapping and g:callIndexAtIsNotOverlapping)
        g:argIndexAtIsNotOverlapping = util:ConfigUpdateObjects(g:argIndexAtIsNotOverlapping, g:updateCheck);
        g:updateArgIndexAtIsNotOverlapping = false;
    end
    
    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    for (i = 0 to aObjects.last)
        coord cAnchor = aObjects[i].anchor;
        
        for (j = 0 to aObjects[i].last)
            coord cRelativePos = util:RelativePos(cAnchor, aObjects[i][j]);
            coord cPos = [iX + cRelativePos.x * -1, iY + cRelativePos.y * -1];
         
            insert.newrule;
            util:InsertIndex(g:vInsertIndex);
            insert.rule.pos = cPos;
            util:Is(cAnchor);
            
            internal:IndexAtExecuteCalls();
            
            internal:BorderRule();
            internal:ResetBorderFlags();
        end
    end
    
    return true;
end



/******************************************************************************

*/
function->null Replace(int iFrom, int iTo) 
    nested(
        Chance
    )

//
    if (s:debug)
        if (iFrom < 0 or iFrom > 255)
            error("Replace(int iFrom, int iTo) -> iFrom needs to be in range [0-255].");
        end
        
        if (iTo < 0 or iTo > 255)
            error("Replace(int iFrom, int iTo) -> iTo needs to be in range [0-255].");
        end
    end
//

    Insert(iTo).If(IndexAt([0, 0]).Is(iFrom));
    invoke(nested);
end



nested function->null Replace.Chance(float fProbability)

    util:Chance(fProbability);
end



/******************************************************************************

*/
function->null ReplaceNot(int iNot, int iTo) 
    nested(
        Chance
    )

//
    if (s:debug)
        if (iNot < 0 or iNot > 255)
            error("ReplaceNot(int iNot, int iTo) -> iNot needs to be in range [0-255].");
        end
        
        if (iTo < 0 or iTo > 255)
            error("ReplaceNot(int iNot, int iTo) -> iTo needs to be in range [0-255].");
        end
    end
//

    Insert(iTo).If(IndexAt([0, 0]).IsNot(iNot));
    invoke(nested);
end



nested function->null ReplaceNot.Chance(float fProbability)

    util:Chance(fProbability);
end



///////////////////////////////////////
//
array int g:argShift;
/******************************************************************************

*/
function->null Shift(array int aIndices)
    nested(
        By
    )

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("Shift(array int aIndices) -> aIndices was empty, function had no effect.");
            return;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < 0 or aIndices[i] > 255)
                error("Shift(array int aIndices) -> values need to be in range [0-255].");
            end
        end
    end
//   

    g:argShift = aIndices;
    invoke(nested);
end



nested function->null Shift.By(coord cPos)

    for (i = 0 to g:argShift.last)
        Insert(0).If(IndexAt([0, 0]).Is(g:argShift[i]));
    end
    for (i = 0 to g:argShift.last)
        Insert(g:argShift[i]).If(IndexAt(cPos).Is(g:argShift[i])).NoDefaultPosRule();
    end
end



///////////////////////////////////////
//
bool g:runInsertObjectTests = false;
bool g:callInsertObjectConfig = true;

bool g:callObjectIsOverlapping = false;
/******************************************************************************

*/
function->null internal:InsertObjectResetFlags()

    g:runInsertObjectTests = false;
    g:runInsertTests = false;
    g:callInsertObjectConfig = true;
end



function->null InsertObject(object oObject)
    nested(
        Config,
        NoDefaultPosRule, Chance, If
    )

//
    if (s:debug)
        if (oObject.count == 0)
            warning("InsertObject(object oObject) -> oObject was empty, function had no effect.");
            return;
        end
    end
//

    util:ResetSettings(g:resetInsert);
    invoke(nested);
    
    g:runInsertObjectTests = true;
    g:runInsertTests = true;

    array object aArray = util:ConfigUpdateObjects(oObject, g:updateInsert);
    for (i = 0 to aArray.last)
        g:vInsertObject = aArray[i];
        g:vInsertIndex = aArray[i].anchor;
        
        invoke(nested);
    end
    internal:InsertObjectResetFlags();
end



nested function->null InsertObject.Config(array int aSettings)

    if (g:callInsertObjectConfig)
        util:ConfigUpdate(aSettings, g:updateInsert);
        
        g:callInsertObjectConfig = false;
    end
end



nested function->null InsertObject.NoDefaultPosRule()

    if (g:runInsertObjectTests)
        util:NoDefaultPosRule();
    end
end



nested function->null InsertObject.Chance(float fProbability)

    if (g:runInsertObjectTests)
        util:Chance(fProbability);
    end
end



nested function->null InsertObject.If(array bool bTests)
end



///////////////////////////////////////
//
bool g:runObjectTests = false;
bool g:callObjectConfig = true;

bool g:callObjectIsNotOverlapping = false;
bool g:callObjectHasSpace         = false;
bool g:callObjectFits             = false;
bool g:callObjectIsOver           = false;
bool g:callObjectIsEdge           = false;
bool g:callObjectIsNotEdge        = false;
bool g:callObjectIsNextTo         = false;
bool g:callObjectIsNotNextTo      = false;

bool g:updateArgObjectIsNotOverlapping = true;
array object g:argObjectIsNotOverlapping;

bool g:updateArgObjectIsOver = true;
array object g:argObjectIsOver;

bool g:updateArgObjectIsNotNextTo = true;
array object g:argObjectIsNotNextTo;

bool g:updateArgObjectIsNextTo = true;
array object g:argObjectIsNextTo;

int g:argObjectIsEdge = 0;

array int g:argObjectIsNotEdge;

int g:vObjectTop    = 0;
int g:vObjectRight  = 0;
int g:vObjectBottom = 0;
int g:vObjectLeft   = 0;
/******************************************************************************

*/
function->null internal:ObjectResetFlags()
    
    g:runObjectTests = false;
    g:callObjectConfig = true;

    g:callObjectIsNotOverlapping = false;
    g:callObjectHasSpace         = false;
    g:callObjectFits             = false;
    g:callObjectIsOver           = false;
    g:callObjectIsEdge           = false;
    g:callObjectIsNotEdge        = false;
    g:callObjectIsNextTo         = false;
    g:callObjectIsNotNextTo      = false;
    g:callObjectIsOverlapping    = false;
    
    g:updateArgObjectIsNotOverlapping = true;
    g:updateArgObjectIsOver           = true;
    g:updateArgObjectIsNotNextTo      = true;
    g:updateArgObjectIsNextTo         = true;
end



function->bool Object()
    nested(
        Config,
        HasSpace, Fits, IsOver,
        IsEdge, IsNotEdge,
        IsNextTo, IsNotNextTo,
        IsNotOverlapping, IsOverlapping
    )

    if (g:runInsertObjectTests == false)
        return false;
    end

    insert.nocopy;
    util:ResetSettings(g:resetCheck);
    invoke(nested);
    
    g:runObjectTests = true;
    g:callObjectConfig = false;
    
    if (g:callObjectIsNotEdge or g:callObjectIsEdge)
        array int aRect = util:Rect(g:vInsertObject);
        g:vObjectTop    = aRect[0];
        g:vObjectRight  = aRect[1];
        g:vObjectBottom = aRect[2];
        g:vObjectLeft   = aRect[3];
    end
    
    if (g:callObjectIsOverlapping == false and g:callObjectIsNextTo == false)
        insert.newrule;
        util:InsertIndex(g:vInsertIndex);
    end
    invoke(nested);
    
    internal:ObjectResetFlags();
    return true;
end



nested function->bool Object.Config(array int aSettings)

    if (g:callObjectConfig)
        util:ConfigUpdate(aSettings, g:updateCheck);
        
        g:callObjectConfig = false;
    end
    return true;
end



function->bool internal:ObjectHasSpace()

    object oObject = g:vInsertObject;
    coord cAnchor = g:vInsertIndex;
    
    for (i = 0 to oObject.last)        
        insert.rule.pos = util:RelativePos(cAnchor, oObject[i]);
        insert.rule.pos.type = full;
    end
    return true;
end



nested function->bool Object.HasSpace()

    if (g:runObjectTests == false)
        g:callObjectHasSpace = true;
        return false;
    end
    if (g:callObjectIsOverlapping or g:callObjectFits)
        return false;
    end

    return internal:ObjectHasSpace();
end



function->bool internal:ObjectFits()
        
    object oObject = g:vInsertObject;
    coord cAnchor = g:vInsertIndex;    
    
    array coord aRelativePos;
    for (i = 0 to oObject.last)
        coord cRelativePos = util:RelativePos(cAnchor, oObject[i]);
        
        aRelativePos.push(cRelativePos);
        
        insert.rule.pos = cRelativePos;
        insert.rule.pos.type = full;
    end
    
    for (i = 0 to aRelativePos.last)
        coord cPos = aRelativePos[i];
        
        coord cTop    = [cPos.x, cPos.y - 1];
        coord cRight  = [cPos.x + 1, cPos.y];
        coord cBottom = [cPos.x, cPos.y + 1];
        coord cLeft   = [cPos.x - 1, cPos.y];
        
        if (aRelativePos.has(cTop) == false)
            insert.rule.pos = cTop;
            insert.rule.pos.type = empty;
        end
        if (aRelativePos.has(cRight) == false)
            insert.rule.pos = cRight;
            insert.rule.pos.type = empty;
        end
        if (aRelativePos.has(cBottom) == false)
            insert.rule.pos = cBottom;
            insert.rule.pos.type = empty;
        end
        if (aRelativePos.has(cLeft) == false)
            insert.rule.pos = cLeft;
            insert.rule.pos.type = empty;
        end
    end
    return true;
end



nested function->bool Object.Fits()

    if (g:runObjectTests == false)
        g:callObjectFits = true;
        return false;
    end
    if (g:callObjectIsOverlapping)
        return false;
    end
        
    return internal:ObjectFits();
end



function->bool internal:ObjectIsOver()

    insert.rule.pos = [0, 0];
    for (i = 0 to g:argObjectIsOver.last)
        util:Is(g:argObjectIsOver[i].anchor);
    end
    return true;
end



nested function->bool Object.IsOver(array object aObjects)

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("IsOver(array object aObjects) -> aObjects was empty, function had no effect.");
            return false;
        end
    end
//

    if (g:runObjectTests == false)
        g:callObjectIsOver = true;
        
        g:argObjectIsOver = aObjects;
        return false;
    end
    if (g:callObjectIsOverlapping)
        return false;
    end
    
    if (g:updateArgObjectIsOver and g:callObjectIsOver)
        g:argObjectIsOver = util:ConfigUpdateObjects(g:argObjectIsOver, g:updateCheck);
        g:updateArgObjectIsOver = false;
    end
    
    return internal:ObjectIsOver();
end



function->bool internal:ObjectIsEdge()

    if (g:argObjectIsEdge == top)
        insert.rule.pos = [0, g:vObjectTop - 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        return true;
    end
    if (g:argObjectIsEdge == right)
        insert.rule.pos = [g:vObjectRight + 1, 0];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        return true;
    end
    if (g:argObjectIsEdge == bottom)
        insert.rule.pos = [0, g:vObjectBottom + 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        return true;
    end
    if (g:argObjectIsEdge == left)
        insert.rule.pos = [g:vObjectLeft - 1, 0];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        return true;
    end
    if (g:argObjectIsEdge == topLeft)
        insert.rule.pos = [0, g:vObjectTop - 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        insert.rule.pos = [g:vObjectLeft - 1, 0];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        return true;
    end
    if (g:argObjectIsEdge == topRight)
        insert.rule.pos = [0, g:vObjectTop - 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        insert.rule.pos = [g:vObjectRight + 1, 0];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        return true;
    end
    if (g:argObjectIsEdge == bottomLeft)
        insert.rule.pos = [0, g:vObjectBottom + 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        insert.rule.pos = [g:vObjectLeft - 1, 0];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        return true;
    end
    if (g:argObjectIsEdge == bottomRight)
        insert.rule.pos = [0, g:vObjectBottom + 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        insert.rule.pos = [g:vObjectRight + 1, 0];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;
        
        return true;
    end
    return true;
end



nested function->bool Object.IsEdge(int iOrientation)

    if (g:runObjectTests == false)
        g:callObjectIsEdge = true;
        
        g:argObjectIsEdge = iOrientation;
        return false;
    end
    if (g:callObjectIsOverlapping)
        return false;
    end
    
    return internal:ObjectIsEdge();
end



function->bool internal:ObjectIsNotEdge()

    for (i = 0 to g:argObjectIsNotEdge.last)
        if (g:argObjectIsNotEdge[i] == top)
            insert.rule.pos = [0, g:vObjectTop - 1];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (g:argObjectIsNotEdge[i] == right)
            insert.rule.pos = [g:vObjectRight + 1, 0];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (g:argObjectIsNotEdge[i] == bottom)
            insert.rule.pos = [0, g:vObjectBottom + 1];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (g:argObjectIsNotEdge[i] == left)
            insert.rule.pos = [g:vObjectLeft - 1, 0];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
    end
    return true;
end



nested function->bool Object.IsNotEdge(array int aOrientations)

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IsNotEdge(array int aOrientations) -> aOrientations was empty, function had no effect.");
            return false;
        end
    end
//

    if (g:runObjectTests == false)
        g:callObjectIsNotEdge = true;
        
        g:argObjectIsNotEdge = aOrientations;
        return false;
    end
    if (g:callObjectIsOverlapping)
        return false;
    end
    
    return internal:ObjectIsNotEdge();
end



function->bool internal:ObjectIsNotNextTo()

    object oObject = g:vInsertObject;
    coord cAnchor = g:vInsertIndex;
    
    for (i = 0 to g:argObjectIsNotNextTo.last)
        coord cOtherAnchor = g:argObjectIsNotNextTo[i].anchor;
        
        array coord aPos;
        for (j = 0 to g:argObjectIsNotNextTo[i].last)
            coord cOtherRelativePos = util:RelativePos(cOtherAnchor, g:argObjectIsNotNextTo[i][j]);
            
            for (k = 0 to oObject.last)
                coord cRelativePos = util:RelativePos(cAnchor, oObject[k]);
                
                coord cPos = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y];
                if (aPos.has(cPos) == false)
                    aPos.push(cPos);
                    
                    insert.rule.pos = cPos;
                    util:IsNot(cOtherAnchor);
                end
                
                insert.rule.pos = [cRelativePos.x - cOtherRelativePos.x - 1, cRelativePos.y - cOtherRelativePos.y];
                util:IsNot(cOtherAnchor);
                
                insert.rule.pos = [cRelativePos.x - cOtherRelativePos.x + 1, cRelativePos.y - cOtherRelativePos.y];
                util:IsNot(cOtherAnchor);
                
                insert.rule.pos = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y - 1];
                util:IsNot(cOtherAnchor);
                
                insert.rule.pos = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y + 1];
                util:IsNot(cOtherAnchor);
            end            
        end
    end
    return true;
end



nested function->bool Object.IsNotNextTo(array object aObjects)

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("IsNotNextTo(array object aObjects) -> aObjects was empty, function had no effect.");
            return false;
        end
    end
//

    if (g:runObjectTests == false)
        g:callObjectIsNotNextTo = true;
        
        g:argObjectIsNotNextTo = aObjects;
        return false;
    end
    if (g:callObjectIsOverlapping)
        return false;
    end
    
    if (g:updateArgObjectIsNotNextTo and g:callObjectIsNotNextTo)
        g:argObjectIsNotNextTo = util:ConfigUpdateObjects(g:argObjectIsNotNextTo, g:updateCheck);
        g:updateArgObjectIsNotNextTo = false;
    end
    
    return internal:ObjectIsNotNextTo();
end



function->bool internal:ObjectIsNotOverlapping()

    object oObject = g:vInsertObject;
    coord cAnchor = g:vInsertIndex;
    
    for (i = 0 to g:argObjectIsNotOverlapping.last)
        coord cOtherAnchor = g:argObjectIsNotOverlapping[i].anchor;
        
        array coord aPos;
        for (j = 0 to g:argObjectIsNotOverlapping[i].last)
            coord cOtherRelativePos = util:RelativePos(cOtherAnchor, g:argObjectIsNotOverlapping[i][j]);
            
            for (k = 0 to oObject.last)
                coord cRelativePos = util:RelativePos(cAnchor, oObject[k]);
                
                coord cPos = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y];
                if (aPos.has(cPos) == false)
                    aPos.push(cPos);
                    
                    insert.rule.pos = cPos;
                    util:IsNot(cOtherAnchor);
                end
            end
        end
    end
    return true;
end



nested function->bool Object.IsNotOverlapping(array object aObjects)
    
//
    if (s:debug)
        if (aObjects.count == 0)
            warning("IsNotOverlapping(array object aObjects) -> aObjects was empty, function had no effect.");
            return false;
        end
    end
//

    if (g:runObjectTests == false)
        g:callObjectIsNotOverlapping = true;
        
        g:argObjectIsNotOverlapping = aObjects;
        return false;
    end
    if (g:callObjectIsOverlapping)
        return false;
    end
    
    if (g:updateArgObjectIsNotOverlapping and g:callObjectIsNotOverlapping)
        g:argObjectIsNotOverlapping = util:ConfigUpdateObjects(g:argObjectIsNotOverlapping, g:updateCheck);
        g:updateArgObjectIsNotOverlapping = false;
    end
    
    return internal:ObjectIsNotOverlapping();
end



function->null internal:ObjectExecuteCalls()

    if (g:callObjectHasSpace and g:callObjectFits == false)
        internal:ObjectHasSpace();
    end
    if (g:callObjectFits)
        internal:ObjectFits();
    end
    if (g:callObjectIsNotOverlapping)
        internal:ObjectIsNotOverlapping();
    end
    if (g:callObjectIsEdge)
        internal:ObjectIsEdge();
    end
    if (g:callObjectIsNotEdge)
        internal:ObjectIsNotEdge();
    end
    if (g:callObjectIsOver)
        internal:ObjectIsOver();
    end
end



function->bool internal:ObjectIsNextTo()

    object oObject = g:vInsertObject;
    coord cAnchor = g:vInsertIndex;
    
    array coord aNextToPos;    
    for (i = 0 to g:argObjectIsNextTo.last)
        coord cOtherAnchor = g:argObjectIsNextTo[i].anchor;
        
        array coord aPos;
        for (j = 0 to g:argObjectIsNextTo[i].last)
            coord cOtherRelativePos = util:RelativePos(cOtherAnchor, g:argObjectIsNextTo[i][j]);
            
            for (k = 0 to oObject.last)
                coord cRelativePos = util:RelativePos(cAnchor, oObject[k]);
                
                coord cPos1 = [cRelativePos.x - cOtherRelativePos.x - 1, cRelativePos.y - cOtherRelativePos.y];
                coord cPos2 = [cRelativePos.x - cOtherRelativePos.x + 1, cRelativePos.y - cOtherRelativePos.y];
                coord cPos3 = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y - 1];                
                coord cPos4 = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y + 1];
                
                if (aNextToPos.has(cPos1) == false)
                    aNextToPos.push(cPos1);
                end
                if (aNextToPos.has(cPos2) == false)
                    aNextToPos.push(cPos2);
                end
                if (aNextToPos.has(cPos3) == false)
                    aNextToPos.push(cPos3);
                end
                if (aNextToPos.has(cPos4) == false)
                    aNextToPos.push(cPos4);
                end
            end            
        end
    end
    
    for (n = 0 to aNextToPos.last)        
        for (i = 0 to g:argObjectIsNextTo.last)
            coord cOtherAnchor = g:argObjectIsNextTo[i].anchor;
            
            insert.newrule;
            util:InsertIndex(cAnchor);
            insert.rule.pos = aNextToPos[n];
            util:Is(cOtherAnchor);
        
            array coord aPos;
            for (j = 0 to g:argObjectIsNextTo[i].last)
                coord cOtherRelativePos = util:RelativePos(cOtherAnchor, g:argObjectIsNextTo[i][j]);
                
                for (k = 0 to oObject.last)
                    coord cRelativePos = util:RelativePos(cAnchor, oObject[k]);
                    
                    coord cPos = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y];
                    if (aPos.has(cPos) == false)
                        aPos.push(cPos);
                        
                        insert.rule.pos = cPos;
                        util:IsNot(cOtherAnchor);
                    end
                end            
            end
            
            internal:ObjectExecuteCalls();
        end
    end
    return true;
end



nested function->bool Object.IsNextTo(array object aObjects)

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("IsNextTo(array object aObjects) -> aObjects was empty, function had no effect.");
            return false;
        end
    end
//

    if (g:runObjectTests == false)
        g:callObjectIsNextTo = true;
        
        g:argObjectIsNextTo = aObjects;
        return false;
    end
    
    if (g:updateArgObjectIsNextTo and g:callObjectIsNextTo)
        g:argObjectIsNextTo = util:ConfigUpdateObjects(g:argObjectIsNextTo, g:updateCheck);
        g:updateArgObjectIsNextTo = false;
    end
    
    return internal:ObjectIsNextTo();
end



nested function->bool Object.IsOverlapping(array object aObjects)

    if (g:runObjectTests == false)
        g:callObjectIsOverlapping = true;
        return false;
    end

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("IsOverlapping(array object aObjects) -> aObjects was empty, function had no effect.");
            return false;
        end
    end
//

    if (g:updateArgObjectIsNotOverlapping and g:callObjectIsNotOverlapping)
        g:argObjectIsNotOverlapping = util:ConfigUpdateObjects(g:argObjectIsNotOverlapping, g:updateCheck);
        g:updateArgObjectIsNotOverlapping = false;
    end
    if (g:updateArgObjectIsOver and g:callObjectIsOver)
        g:argObjectIsOver = util:ConfigUpdateObjects(g:argObjectIsOver, g:updateCheck);
        g:updateArgObjectIsOver = false;
    end
    
    array object aArray = util:ConfigUpdateObjects(aObjects, g:updateCheck);
    
    object oObject = g:vInsertObject;
    coord cAnchor = g:vInsertIndex;
    
    for (i = 0 to aArray.last)        
        coord cOtherAnchor = aArray[i].anchor;
        
        array coord aPos;
        for (j = 0 to aArray[i].last)
            coord cOtherRelativePos = util:RelativePos(cOtherAnchor, aArray[i][j]);
            
            for (k = 0 to oObject.last)
                coord cRelativePos = util:RelativePos(cAnchor, oObject[k]);
                
                coord cPos = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y];
                if (aPos.has(cPos) == false)
                    aPos.push(cPos);
                    
                    insert.newrule;
                    util:InsertIndex(cAnchor);
                    
                    insert.rule.pos = cPos;
                    util:Is(cOtherAnchor);

                    internal:ObjectExecuteCalls();
                end
            end
        end
    end
    return true;
end
