
///////////////////////////////////////
// global variables (internal)
///////////////////////////////////////
/******************************************************************************

*/
// value holders
int g:vInsertIndex = 0;
object g:vInsertObject;

array int g:vTestIndices;

// values
int g:intMax = 2147483647;
int g:intMin = -2147483648;

int g:and = 0;
int g:or = 1;
int g:group = 0;
int g:mask = 255;



///////////////////////////////////////
// settings
///////////////////////////////////////
/******************************************************************************

*/
bool s:debug = true;



///////////////////////////////////////
//
int top         = 1000;
int right       = 1001;
int bottom      = 1002;
int left        = 1003;
int topLeft     = 1004;
int topRight    = 1005;
int bottomRight = 1006;
int bottomLeft  = 1007;
int all         = 1008;
int vertical    = 1009;
int horizontal  = 1010;
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



function->bool util:SameRotation(int iIndex1, int iIndex2)

    return iIndex1.rotate.V == iIndex2.rotate.V
       and iIndex1.rotate.H == iIndex2.rotate.H
       and iIndex1.rotate.R == iIndex2.rotate.R;
end



function->int util:RemoveRotation(int iIndex)

    float fIndex = iIndex;
    return fIndex;
end



function->array int util:RemoveRotation(array int aIndices)

    array int aResult;
    if (aIndices.count != 0)
        for (i = 0 to aIndices.last)
            aResult.push(util:RemoveRotation(aIndices[i]));
        end
    end
    return aResult;
end



function->int util:EnsureRotation(int iIndex)

    bool hasV = iIndex.rotate.V;
    bool hasH = iIndex.rotate.H;
    bool hasR = iIndex.rotate.R;

    if (hasV or hasH or hasR)
        return iIndex;
    end
    return iIndex.N;
end



function->array int util:EnsureRotation(array int aIndices)

    array int aResult;
    if (aIndices.count != 0)
        for (i = 0 to aIndices.last)
            aResult.push(util:EnsureRotation(aIndices[i]));
        end
    end
    return aResult;
end



function->int util:N(int iIndex)

    return iIndex.N;
end



function->array int util:N(array int aIndices)

    array int aResult;

    if (aIndices.count != 0)
        array int aArray = aIndices.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].N);
        end
    end
    return aResult;
end



function->object util:N(object oObject)

    return oObject.N;
end



function->array object util:N(array object aObjects)

    array object aResult;

    if (aObjects.count != 0)
        array object aArray = aObjects.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].N);
        end
    end
    return aResult;
end



function->int util:V(int iIndex)

    return iIndex.V;
end



function->array int util:V(array int aIndices)

    array int aResult;

    if (aIndices.count != 0)
        array int aArray = aIndices.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].V);
        end
    end
    return aResult;
end



function->object util:V(object oObject)

    return oObject.V;
end



function->array object util:V(array object aObjects)

    array object aResult;

    if (aObjects.count != 0)
        array object aArray = aObjects.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].V);
        end
    end
    return aResult;
end



function->int util:H(int iIndex)

    return iIndex.H;
end



function->array int util:H(array int aIndices)

    array int aResult;

    if (aIndices.count != 0)
        array int aArray = aIndices.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].H);
        end
    end
    return aResult;
end



function->object util:H(object oObject)

    return oObject.H;
end



function->array object util:H(array object aObjects)

    array object aResult;

    if (aObjects.count != 0)
        array object aArray = aObjects.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].H);
        end
    end
    return aResult;
end



function->int util:R(int iIndex)

    return iIndex.R;
end



function->array int util:R(array int aIndices)

    array int aResult;

    if (aIndices.count != 0)
        array int aArray = aIndices.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].R);
        end
    end
    return aResult;
end



function->object util:R(object oObject)

    return oObject.R;
end



function->array object util:R(array object aObjects)

    array object aResult;

    if (aObjects.count != 0)
        array object aArray = aObjects.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].R);
        end
    end
    return aResult;
end



function->int util:VH(int iIndex)

    return iIndex.VH;
end



function->array int util:VH(array int aIndices)

    array int aResult;

    if (aIndices.count != 0)
        array int aArray = aIndices.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].VH);
        end
    end
    return aResult;
end



function->object util:VH(object oObject)

    return oObject.VH;
end



function->array object util:VH(array object aObjects)

    array object aResult;

    if (aObjects.count != 0)
        array object aArray = aObjects.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].VH);
        end
    end
    return aResult;
end



function->int util:VR(int iIndex)

    return iIndex.VR;
end



function->array int util:VR(array int aIndices)

    array int aResult;

    if (aIndices.count != 0)
        array int aArray = aIndices.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].VR);
        end
    end
    return aResult;
end



function->object util:VR(object oObject)

    return oObject.VR;
end



function->array object util:VR(array object aObjects)

    array object aResult;

    if (aObjects.count != 0)
        array object aArray = aObjects.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].VR);
        end
    end
    return aResult;
end



function->int util:HR(int iIndex)

    return iIndex.HR;
end



function->array int util:HR(array int aIndices)

    array int aResult;

    if (aIndices.count != 0)
        array int aArray = aIndices.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].HR);
        end
    end
    return aResult;
end



function->object util:HR(object oObject)

    return oObject.HR;
end



function->array object util:HR(array object aObjects)

    array object aResult;

    if (aObjects.count != 0)
        array object aArray = aObjects.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].HR);
        end
    end
    return aResult;
end



function->int util:VHR(int iIndex)

    return iIndex.VHR;
end



function->array int util:VHR(array int aIndices)

    array int aResult;

    if (aIndices.count != 0)
        array int aArray = aIndices.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].VHR);
        end
    end
    return aResult;
end



function->object util:VHR(object oObject)

    return oObject.VHR;
end



function->array object util:VHR(array object aObjects)

    array object aResult;

    if (aObjects.count != 0)
        array object aArray = aObjects.unique();

        for (i = 0 to aArray.last)
            aResult.push(aArray[i].VHR);
        end
    end
    return aResult;
end



function->array int util:Rotations(int iIndex)

    array int aResult;
    aResult.push(iIndex.N);
    aResult.push(iIndex.R);
    aResult.push(iIndex.VH);
    aResult.push(iIndex.VHR);
    return aResult;
end



function->array int util:Rotations(array int aIndices)

    array int aResult;

    if (aIndices.count != 0)
        array int aArray = aIndices.unique();

        for (i = 0 to aArray.last)
            int iIndex = aArray[i];
            aResult.push(iIndex.N);
            aResult.push(iIndex.R);
            aResult.push(iIndex.VH);
            aResult.push(iIndex.VHR);
        end
    end
    return aResult;
end



function->array object util:Rotations(object oObject)

    array object aResult;
    aResult.push(oObject.N);
    aResult.push(oObject.R);
    aResult.push(oObject.VH);
    aResult.push(oObject.VHR);
    return aResult;
end



function->array object util:Rotations(array object aObjects)

    array object aResult;

    if (aObjects.count != 0)
        array object aArray = aObjects.unique();

        for (i = 0 to aArray.last)
            object oObject = aArray[i];
            aResult.push(oObject.N);
            aResult.push(oObject.R);
            aResult.push(oObject.VH);
            aResult.push(oObject.VHR);
        end
    end
    return aResult;
end



function->array int util:Mirrors(int iIndex)

    array int aResult;
    aResult.push(iIndex.V);
    aResult.push(iIndex.H);
    aResult.push(iIndex.VR);
    aResult.push(iIndex.HR);
    return aResult;
end



function->array int util:Mirrors(array int aIndices)

    array int aResult;

    if (aIndices.count != 0)
        array int aArray = aIndices.unique();

        for (i = 0 to aArray.last)
            int iIndex = aArray[i];
            aResult.push(iIndex.V);
            aResult.push(iIndex.H);
            aResult.push(iIndex.VR);
            aResult.push(iIndex.HR);
        end
    end
    return aResult;
end



function->array object util:Mirrors(object oObject)

    array object aResult;
    aResult.push(oObject.V);
    aResult.push(oObject.H);
    aResult.push(oObject.VR);
    aResult.push(oObject.HR);
    return aResult;
end



function->array object util:Mirrors(array object aObjects)

    array object aResult;

    if (aObjects.count != 0)
        array object aArray = aObjects.unique();

        for (i = 0 to aArray.last)
            object oObject = aArray[i];
            aResult.push(oObject.V);
            aResult.push(oObject.H);
            aResult.push(oObject.VR);
            aResult.push(oObject.HR);
        end
    end
    return aResult;
end



function->array int util:All(int iIndex)

    array int aResult;
    aResult.push(iIndex.N);
    aResult.push(iIndex.V);
    aResult.push(iIndex.H);
    aResult.push(iIndex.R);
    aResult.push(iIndex.VH);
    aResult.push(iIndex.VR);
    aResult.push(iIndex.HR);
    aResult.push(iIndex.VHR);
    return aResult;
end



function->array int util:All(array int aIndices)

    array int aResult;

    if (aIndices.count != 0)
        array int aArray = aIndices.unique();

        for (i = 0 to aArray.last)
            int iIndex = aArray[i];
            aResult.push(iIndex.N);
            aResult.push(iIndex.V);
            aResult.push(iIndex.H);
            aResult.push(iIndex.R);
            aResult.push(iIndex.VH);
            aResult.push(iIndex.VR);
            aResult.push(iIndex.HR);
            aResult.push(iIndex.VHR);
        end
    end
    return aResult;
end



function->array object util:All(object oObject)

    array object aResult;
    aResult.push(oObject.N);
    aResult.push(oObject.V);
    aResult.push(oObject.H);
    aResult.push(oObject.R);
    aResult.push(oObject.VH);
    aResult.push(oObject.VR);
    aResult.push(oObject.HR);
    aResult.push(oObject.VHR);
    return aResult;
end



function->array object util:All(array object aObjects)

    array object aResult;

    if (aObjects.count != 0)
        array object aArray = aObjects.unique();

        for (i = 0 to aArray.last)
            object oObject = aArray[i];
            aResult.push(oObject.N);
            aResult.push(oObject.V);
            aResult.push(oObject.H);
            aResult.push(oObject.R);
            aResult.push(oObject.VH);
            aResult.push(oObject.VR);
            aResult.push(oObject.HR);
            aResult.push(oObject.VHR);
        end
    end
    return aResult;
end



function->int util:Rotate(int iIndex)

    bool hasV = iIndex.rotate.V;
    bool hasH = iIndex.rotate.H;
    bool hasR = iIndex.rotate.R;

    if (hasV and hasH and hasR)
        return iIndex.N;
    end
    if (hasV and hasH)
        return iIndex.VHR;
    end
    if (hasV and hasR)
        return iIndex.H;
    end
    if (hasH and hasR)
        return iIndex.V;
    end
    if (hasV)
        return iIndex.VR;
    end
    if (hasH)
        return iIndex.HR;
    end
    if (hasR)
        return iIndex.VH;
    end

    return iIndex.R;
end



function->array int util:Rotate(array int aIndices)

    array int aResult;

    for (i = 0 to aIndices.last)
        aResult.push(util:Rotate(aIndices[i]));
    end
    return aResult;
end



function->object util:Rotate(object oObject)

    bool hasV = oObject.rotate.V;
    bool hasH = oObject.rotate.H;
    bool hasR = oObject.rotate.R;

    if (hasV and hasH and hasR)
        return oObject.N;
    end
    if (hasV and hasH)
        return oObject.VHR;
    end
    if (hasV and hasR)
        return oObject.H;
    end
    if (hasH and hasR)
        return oObject.V;
    end
    if (hasV)
        return oObject.VR;
    end
    if (hasH)
        return oObject.HR;
    end
    if (hasR)
        return oObject.VH;
    end

    return oObject.R;
end



function->array object util:Rotate(array object aObjects)

    array object aResult;

    for (i = 0 to aObjects.last)
        aResult.push(util:Rotate(aObjects[i]));
    end
    return aResult;
end



function->int util:MirrorV(int iIndex)

    bool hasV = iIndex.rotate.V;
    bool hasH = iIndex.rotate.H;
    bool hasR = iIndex.rotate.R;

    if (hasV and hasH and hasR)
        return iIndex.VR;
    end
    if (hasV and hasH)
        return iIndex.H;
    end
    if (hasV and hasR)
        return iIndex.VHR;
    end
    if (hasH and hasR)
        return iIndex.R;
    end
    if (hasV)
        return iIndex.N;
    end
    if (hasH)
        return iIndex.VH;
    end
    if (hasR)
        return iIndex.HR;
    end

    return iIndex.V;
end



function->array int util:MirrorV(array int aIndices)

    array int aResult;

    for (i = 0 to aIndices.last)
        aResult.push(util:MirrorV(aIndices[i]));
    end
    return aResult;
end



function->object util:MirrorV(object oObject)

    bool hasV = oObject.rotate.V;
    bool hasH = oObject.rotate.H;
    bool hasR = oObject.rotate.R;

    if (hasV and hasH and hasR)
        return oObject.VR;
    end
    if (hasV and hasH)
        return oObject.H;
    end
    if (hasV and hasR)
        return oObject.VHR;
    end
    if (hasH and hasR)
        return oObject.R;
    end
    if (hasV)
        return oObject.N;
    end
    if (hasH)
        return oObject.VH;
    end
    if (hasR)
        return oObject.HR;
    end

    return oObject.V;
end



function->array object util:MirrorV(array object aObjects)

    array object aResult;

    for (i = 0 to aObjects.last)
        aResult.push(util:MirrorV(aObjects[i]));
    end
    return aResult;
end



function->int util:MirrorH(int iIndex)

    bool hasV = iIndex.rotate.V;
    bool hasH = iIndex.rotate.H;
    bool hasR = iIndex.rotate.R;

    if (hasV and hasH and hasR)
        return iIndex.HR;
    end
    if (hasV and hasH)
        return iIndex.V;
    end
    if (hasV and hasR)
        return iIndex.R;
    end
    if (hasH and hasR)
        return iIndex.VHR;
    end
    if (hasV)
        return iIndex.VH;
    end
    if (hasH)
        return iIndex.N;
    end
    if (hasR)
        return iIndex.VR;
    end

    return iIndex.H;
end



function->array int util:MirrorH(array int aIndices)

    array int aResult;

    for (i = 0 to aIndices.last)
        aResult.push(util:MirrorH(aIndices[i]));
    end
    return aResult;
end



function->object util:MirrorH(object oObject)

    bool hasV = oObject.rotate.V;
    bool hasH = oObject.rotate.H;
    bool hasR = oObject.rotate.R;

    if (hasV and hasH and hasR)
        return oObject.HR;
    end
    if (hasV and hasH)
        return oObject.V;
    end
    if (hasV and hasR)
        return oObject.R;
    end
    if (hasH and hasR)
        return oObject.VHR;
    end
    if (hasV)
        return oObject.VH;
    end
    if (hasH)
        return oObject.N;
    end
    if (hasR)
        return oObject.VR;
    end

    return oObject.H;
end



function->array object util:MirrorH(array object aObjects)

    array object aResult;

    for (i = 0 to aObjects.last)
        aResult.push(util:MirrorH(aObjects[i]));
    end
    return aResult;
end



function->bool util:Is(int iIndex)

//
    if (s:debug)
        if (iIndex < -1 or iIndex > 255)
            error("util:Is(int " + iIndex.name() + ") -> " + iIndex.name() + " needs to be in range [-1-255].");
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
            warning("util:Is(array int " + aIndices.name() + ") -> " + aIndices.name() + " was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < -1 or aIndices[i] > 255)
                error("util:Is(array int " + aIndices.name() + ") -> values need to be in range [-1-255].");
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
            error("util:IsNot(int " + iIndex.name() + ") -> " + iIndex.name() + " needs to be in range [-1-255].");
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
            warning("util:IsNot(array int " + aIndices.name() + ") -> " + aIndices.name() + " was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < -1 or aIndices[i] > 255)
                error("util:IsNot(array int " + aIndices.name() + ") -> values need to be in range [-1-255].");
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
            error("util:InsertIndex(int " + iIndex.name() + ") -> value needs to be in range [0-255].");
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



function->array float util:CopiesOf(int iCopies, float fValue)

//
    if (s:debug)
        if (iCopies < 1)
            error("util:CopiesOf(int " + iCopies.name() + ", float " + fValue.name() + ") -> " + iCopies.name() + " needs to be greater than 0.");
        end
    end
//

    array float aResult;
    for (i = 0 to iCopies - 1)
        aResult.push(fValue);
    end
    return aResult;
end



function->int util:Negate(int iValue)

    return iValue * -1;
end



function->coord util:Negate(coord cValue)

    return [cValue.x * -1, cValue.y * -1];
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



function->bool util:Found(int iResult)

    return iResult != -1;
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
            error("util:Rect(object " + oObject.name() + ") -> " + oObject.name() + " cannot be empty.");
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
            error("util:Size(object " + oObject.name() + ") -> " + oObject.name() + " cannot be empty.");
        end
    end
//

    array int aRect = util:Rect(oObject);
    return [aRect[1] - aRect[3] + 1, aRect[2] - aRect[0] + 1];
end



function->float util:SumOf(array float aValues)

//
    if (s:debug)
        if (aValues.count == 0)
            error("util:SumOf(array float " + aValues.name() + ") -> " + aValues.name() + " cannot be empty.");
        end
    end
//

    float fSum = 0.0;
    for (i = 0 to aValues.last)
        fSum = fSum + aValues[i];
    end
    return fSum;
end



function->array float util:Normalize(array float aValues, float fBound)

//
    if (s:debug)
        if (aValues.count == 0)
            error("util:Normalize(array float " + aValues.name() + ", float " + fBound.name() + ") -> " + aValues.name() + " cannot be empty.");
        end
    end
//

    float fFactor = fBound / util:SumOf(aValues);

    array float aResult;
    for (i = 0 to aValues.last)
        aResult.push(aValues[i] * fFactor);
    end
    return aResult;
end



function->array float util:Unbias(array float aProbabilities)

//
    if (s:debug)
        if (aProbabilities.count == 0)
            error("util:Unbias(array float " + aProbabilities.name() + ") -> " + aProbabilities.name() + " cannot be empty.");
        end
    end
//

    float fSum = util:SumOf(aProbabilities);

    array float aClamped = aProbabilities;
    if (fSum > 100.0)
        aClamped = util:Normalize(aProbabilities, 100.0);
    end

    float fRemaining = 100.0;

    array float aResult;
    for (i = 0 to aClamped.last)
        float fUnbiased = aClamped[i] / fRemaining * 100.0;
        fRemaining = fRemaining - aClamped[i];
        aResult.push(fUnbiased);
    end
    return aResult;
end



function->array float util:ToProbabilities(array float aPercents)

//
    if (s:debug)
        if (aPercents.count == 0)
            error("util:ToProbabilities(array float " + aPercents.name() + ") -> " + aPercents.name() + " cannot be empty.");
        end
    end
//

    array float aResult;
    for (i = 0 to aPercents.last)
        aResult.push(100.0 / aPercents[i]);
    end
    return aResult;
end



function->int util:OppositeSide(int iSide)

//
    if (s:debug)
        if (iSide < top or iSide > left)
            error("util:OppositeSide(int " + iSide.name() + ") -> value needs to be top, right, bottom or left.");
        end
    end
//

    int iResult = iSide + 2;
    if (iResult > left)
        return iResult - 4;
    end
    return iResult;
end





///////////////////////////////////////
//
bool g:randomize = false;
bool g:roll      = false;
bool g:hasAt     = false;
///////////////////////////////////////
// internal utility functions
///////////////////////////////////////
/******************************************************************************

*/
function->null internal:ResetFlags()

    g:randomize = false;
    g:roll      = false;
    g:hasAt     = false;
end



function->bool internal:TestIndicesEmpty()

    if (g:vTestIndices.count != 0)
        insert.rule.pos.type = notindex;
        for (i = 0 to g:vTestIndices.last)
            insert.rule.pos.index = g:vTestIndices[i];
        end
        return true;
    end
    insert.rule.pos.type = empty;
    return true;
end



function->bool internal:TestIndicesFull()

    if (g:vTestIndices.count != 0)
        insert.rule.pos.type = index;
        for (i = 0 to g:vTestIndices.last)
            insert.rule.pos.index = g:vTestIndices[i];
        end
        return true;
    end
    insert.rule.pos.type = full;
    return true;
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
            error("NewRun(int " + iCopies.name() + ") -> " + iCopies.name() + " needs to be greater than 0.");
        end
    end
//

    insert.newrun = iCopies;
end



function->null OverrideLayer()

    insert.nocopy;
end



function->object Indices(array int aIndices)

//
    if (s:debug)
        if (aIndices.count == 0)
            error("Indices(array int " + aIndices.name() + ") -> " + aIndices.name() + " was empty, object would be invalid.");
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < 1 or aIndices[i] > 255)
                error("Indices(array int " + aIndices.name() + ") -> values need to be in range [1-255].");
            end
        end
    end
//

    object oResult = aIndices;
    return oResult;
end



function->object Rect(int iTopLeft, int iBottomRight)

//
    if (s:debug)
        if (iTopLeft < 1 or iTopLeft > 255)
            error("Rect(int " + iTopLeft.name() + ", int " + iBottomRight.name() + ") -> " + iTopLeft.name() + " needs to be in range [1-255].");
        end

        if (iBottomRight < 1 or iBottomRight > 255)
            error("Rect(int " + iTopLeft.name() + ", int " + iBottomRight.name() + ") -> " + iBottomRight.name() + " needs to be in range [1-255].");
        end
    end
//

    coord cTopLeft = iTopLeft;
    coord cBottomRight = iBottomRight;

//
    if (s:debug)
        if (cTopLeft.x > cBottomRight.x or cTopLeft.y > cBottomRight.y)
            warning("Rect(int " + iTopLeft.name() + ", int " + iBottomRight.name() + ") -> " + iTopLeft.name() + " is not the top left corner of the rectangle.");
        end
    end
//

    array int aIndices;
    for (x = cTopLeft.x to cBottomRight.x)
        for (y = cTopLeft.y to cBottomRight.y)
            aIndices.push([x, y]);
        end
    end

    object oResult = aIndices;
    return oResult;
end



function->array coord Area(coord cPos, coord cSize)

//
    if (s:debug)
        if (cSize.x < 1 or cSize.y < 1)
            error("Area(coord " + cPos.name() + ", coord " + cSize.name() + ") -> " + cSize.name() + " needs to be greater than 0.");
        end
    end
//

    array coord aResult;
    
    for (x = cPos.x to cPos.x + cSize.x - 1)
        for (y = cPos.y to cPos.y + cSize.y - 1)
            aResult.push([x, y]);
        end
    end    
    return aResult;
end



function->array coord Radius(coord cPos, int iRadius)

//
    if (s:debug)
        if (iRadius < 0)
            error("Radius(coord " + cPos.name() + ", int " + iRadius.name() + ") -> " + iRadius.name() + " needs to be greater than or equal to 0.");
        end
    end
//

    array coord aResult;

    for (x = util:Negate(iRadius) to iRadius)
        for (y = util:Negate(iRadius) to iRadius)
            int iDiffX = cPos.x - x;
            int iDiffY = cPos.y - y;
            
            if (iDiffX * iDiffX + iDiffY * iDiffY <= iRadius * iRadius)
                aResult.push([x, y]);
            end
        end
    end
    return aResult;
end



function->array coord Footprint(object oObject, int iOrientation)

//
    if (s:debug)
        if (oObject.count == 0)
            error("Footprint(object " + oObject.name() + ", int " + iOrientation.name() + ") -> " + oObject.name() + " cannot be empty.");
        end

        if (iOrientation < top or iOrientation > left)
            error("Footprint(object " + oObject.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be top, right, bottom or left.");
        end
    end
//

    array coord aResult;
    array int aRect = util:Rect(oObject);

    for (i = 0 to oObject.last)
        coord cRelativePos = util:RelativePos(oObject.anchor, oObject[i]);

        if (iOrientation == top and cRelativePos.y == aRect[0])
            aResult.push([cRelativePos.x, cRelativePos.y - 1]);
        end
        if (iOrientation == right and cRelativePos.x == aRect[1])
            aResult.push([cRelativePos.x + 1, cRelativePos.y]);
        end
        if (iOrientation == bottom and cRelativePos.y == aRect[2])
            aResult.push([cRelativePos.x, cRelativePos.y + 1]);
        end
        if (iOrientation == left and cRelativePos.x == aRect[3])
            aResult.push([cRelativePos.x - 1, cRelativePos.y]);
        end
    end
    return aResult;
end



///////////////////////////////////////
//
bool g:initInsert = true;

array float g:argInsertChance;
int g:argInsertChanceIndex = 0;
/******************************************************************************

*/
function->null internal:InsertResetFlags()

    g:initInsert = true;
end



function->null internal:UpdateProbabilities(int iLast)

    if (iLast == 0)
        g:roll = false;
    end

    array float aProbabilities;

    if (not g:roll)
        if (g:randomize)
            for (i = 0 to iLast)
                aProbabilities.push(g:argInsertChance[g:argInsertChanceIndex]);

                g:argInsertChanceIndex = g:argInsertChanceIndex + 1;
                if (g:argInsertChanceIndex > g:argInsertChance.last)
                    g:argInsertChanceIndex = 0;
                end
            end

            g:argInsertChance = util:ToProbabilities(util:Unbias(aProbabilities));
        end
        if (not g:randomize)
            for (i = 0 to iLast)
                aProbabilities.push(1.0);
            end
            g:argInsertChance = aProbabilities;
        end
    end
    if (g:roll)
        for (i = 0 to iLast)
            aProbabilities.push(iLast + 1 - i);
        end
        g:argInsertChance = aProbabilities;
    end

    g:argInsertChanceIndex = 0;
end



function->null Insert(array int aIndices)
    nested(
        At,
        NoDefaultPosRule, Chance, Roll, If
    )

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("Insert(array int " + aIndices.name() + ") -> " + aIndices.name() + " was empty, function had no effect.");
            return;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < 0 or aIndices[i] > 255)
                error("Insert(array int " + aIndices.name() + ") -> values need to be in range [0-255].");
            end
        end
    end
//

    invoke(nested);
    g:initInsert = false;

    internal:UpdateProbabilities(aIndices.last);
    if (g:roll or g:randomize)
        insert.nocopy;
    end

    for (i = 0 to aIndices.last)
        g:vInsertIndex = aIndices[i];

        insert.newrule;
        util:InsertIndex(g:vInsertIndex);
        util:Chance(g:argInsertChance[g:argInsertChanceIndex]);

        invoke(nested);

        g:argInsertChanceIndex = g:argInsertChanceIndex + 1;
    end

    array float aEmpty;
    g:argInsertChance = aEmpty;
    g:argInsertChanceIndex = 0;

    internal:InsertResetFlags();
    internal:ResetFlags();
end



nested function->null Insert.At(coord cPos)

    if (g:initInsert)
        g:hasAt = true;
        return;
    end

//
    if (s:debug)
        if (cPos.x < 0)
            warning("Insert.At(coord " + cPos.name() + ") -> " + cPos.name() + ".x was negative, function had no effect.");
            return;
        end
        if (cPos.y < 0)
            warning("Insert.At(coord " + cPos.name() + ") -> " + cPos.name() + ".y was negative, function had no effect.");
            return;
        end
    end
//

    coord cPosNegated = util:Negate(cPos);

    insert.rule.pos = cPosNegated;
    insert.rule.pos.type = notindex;
    insert.rule.pos.index = -1;

    insert.rule.pos = [cPosNegated.x - 1, 0];
    insert.rule.pos.type = index;
    insert.rule.pos.index = -1;

    insert.rule.pos = [0, cPosNegated.y - 1];
    insert.rule.pos.type = index;
    insert.rule.pos.index = -1;

    insert.rule.nodefault;
end



nested function->null Insert.NoDefaultPosRule()

    if (g:initInsert)
        return;
    end
    insert.rule.nodefault;
end



nested function->null Insert.Chance(array float aProbabilities)

//
    if (s:debug)
        if (aProbabilities.count == 0)
            warning("Insert.Chance(array float " + aProbabilities.name() + ") -> " + aProbabilities.name() + " was empty, function had no effect.");
            return;
        end

        for (i = 0 to aProbabilities.last)
            if (aProbabilities[i] <= 0)
                error("Insert.Chance(array float " + aProbabilities.name() + ") -> values need to be greater than 0.");
            end
        end
    end
//

    if (g:initInsert)
        g:randomize = true;
        g:argInsertChance = aProbabilities;
        return;
    end
end



nested function->null Insert.Roll()

    if (g:initInsert)
        g:roll = true;
        return;
    end
end



nested function->null Insert.If(array bool bTests)
end



///////////////////////////////////////
//
bool g:initIndexAt = true;

coord g:posIndexAt = [0, 0];

int g:borderTop         = 1;
int g:borderRight       = 1;
int g:borderBottom      = 1;
int g:borderLeft        = 1;
int g:borderTopLeft     = 1;
int g:borderTopRight    = 1;
int g:borderBottomLeft  = 1;
int g:borderBottomRight = 1;

int this = 99999;
/******************************************************************************

*/
function->null internal:IndexAtResetFlags()

    g:initIndexAt = true;

    g:posIndexAt = [0, 0];
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

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    if (g:borderTop         == 0) insert.rule.pos = [iX    , iY - 1]; internal:TestIndicesEmpty(); end
    if (g:borderRight       == 0) insert.rule.pos = [iX + 1, iY    ]; internal:TestIndicesEmpty(); end
    if (g:borderBottom      == 0) insert.rule.pos = [iX    , iY + 1]; internal:TestIndicesEmpty(); end
    if (g:borderLeft        == 0) insert.rule.pos = [iX - 1, iY    ]; internal:TestIndicesEmpty(); end
    if (g:borderTopLeft     == 0) insert.rule.pos = [iX - 1, iY - 1]; internal:TestIndicesEmpty(); end
    if (g:borderTopRight    == 0) insert.rule.pos = [iX + 1, iY - 1]; internal:TestIndicesEmpty(); end
    if (g:borderBottomLeft  == 0) insert.rule.pos = [iX - 1, iY + 1]; internal:TestIndicesEmpty(); end
    if (g:borderBottomRight == 0) insert.rule.pos = [iX + 1, iY + 1]; internal:TestIndicesEmpty(); end

    if (g:borderTop         == 1) insert.rule.pos = [iX    , iY - 1]; internal:TestIndicesFull(); end
    if (g:borderRight       == 1) insert.rule.pos = [iX + 1, iY    ]; internal:TestIndicesFull(); end
    if (g:borderBottom      == 1) insert.rule.pos = [iX    , iY + 1]; internal:TestIndicesFull(); end
    if (g:borderLeft        == 1) insert.rule.pos = [iX - 1, iY    ]; internal:TestIndicesFull(); end
    if (g:borderTopLeft     == 1) insert.rule.pos = [iX - 1, iY - 1]; internal:TestIndicesFull(); end
    if (g:borderTopRight    == 1) insert.rule.pos = [iX + 1, iY - 1]; internal:TestIndicesFull(); end
    if (g:borderBottomLeft  == 1) insert.rule.pos = [iX - 1, iY + 1]; internal:TestIndicesFull(); end
    if (g:borderBottomRight == 1) insert.rule.pos = [iX + 1, iY + 1]; internal:TestIndicesFull(); end
end



function->bool IndexAt(array coord aCoords)
    nested(
        TestIndices,
        Is, IsNot, IsEmpty, IsEmptyAt, IsFull, IsFullAt, IsOut, IsNotOut,
        IsWithinArea, IsNotWithinArea,
        IsWithinRadius, IsNotWithinRadius,
        IsEdge, IsNotEdge,
        IsNextTo, IsNotNextTo,
        IsWall, IsOuterCorner, IsInnerCorner,
        HasSpaceFor,
        IsOverlapping, IsNotOverlapping
    )

//
    if (s:debug)
        if (aCoords.count == 0)
            warning("IndexAt(array coord " + aCoords.name() + ") -> " + aCoords.name() + " was empty, function had no effect.");
            return false;
        end
    end
//

    if (g:initInsert or g:hasAt)
        return false;
    end

    invoke(nested);
    g:initIndexAt = false;

    for (i = 0 to aCoords.last)
        g:posIndexAt = aCoords[i];
        invoke(nested);

        internal:BorderRule();
        internal:ResetBorderFlags();
    end

    array int aEmpty;
    g:vTestIndices = aEmpty;

    internal:IndexAtResetFlags();
    internal:ResetFlags();
    return true;
end



nested function->bool IndexAt.TestIndices(array int aIndices)

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("IndexAt.TestIndices(array int " + aIndices.name() + ") -> " + aIndices.name() + " was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < 0 or aIndices[i] > 255)
                error("IndexAt.TestIndices(array int " + aIndices.name() + ") -> values need to be in range [0-255].");
            end
        end
    end
//

    if (g:initIndexAt)
        g:vTestIndices = aIndices;
        return false;
    end
    return true;
end



nested function->bool IndexAt.Is(array int aIndices)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("IndexAt.Is(array int " + aIndices.name() + ") -> " + aIndices.name() + " was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if ((aIndices[i] < -1 or aIndices[i] > 255) and aIndices[i] != this)
                error("IndexAt.Is(array int " + aIndices.name() + ") -> values need to be in range [-1-255].");
            end
        end
    end
//

    insert.rule.pos = g:posIndexAt;
    insert.rule.pos.type = index;
    for (i = 0 to aIndices.last)
        int iIndex = aIndices[i];
        if (iIndex != this) insert.rule.pos.index = iIndex; end
        if (iIndex == this) insert.rule.pos.index = g:vInsertIndex; end
    end
    return true;
end



nested function->bool IndexAt.IsNot(array int aIndices)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("IndexAt.IsNot(array int " + aIndices.name() + ") -> " + aIndices.name() + " was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if ((aIndices[i] < -1 or aIndices[i] > 255) and aIndices[i] != this)
                error("IndexAt.IsNot(array int " + aIndices.name() + ") -> values need to be in range [-1-255].");
            end
        end
    end
//

    insert.rule.pos = g:posIndexAt;
    insert.rule.pos.type = notindex;
    for (i = 0 to aIndices.last)
        int iIndex = aIndices[i];
        if (iIndex != this) insert.rule.pos.index = iIndex; end
        if (iIndex == this) insert.rule.pos.index = g:vInsertIndex; end
    end
    return true;
end



nested function->bool IndexAt.IsEmpty()

    if (g:initIndexAt)
        return false;
    end

    insert.rule.pos = g:posIndexAt;
    insert.rule.pos.type = empty;
    return true;
end



nested function->bool IndexAt.IsEmptyAt(array int aOrientations)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IndexAt.IsEmptyAt(array int " + aOrientations.name() + ") -> " + aOrientations.name() + " was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aOrientations.last)
            if (aOrientations[i] < top or aOrientations[i] > bottomLeft)
                error("IndexAt.IsEmptyAt(array int " + aOrientations.name() + ") -> values need to be top, right, bottom, left, topLeft, topRight, bottomRight or bottomLeft.");
            end
        end
    end
//

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
        if (iOrientation == bottomRight)
            insert.rule.pos = [iX + 1, iY + 1];
            insert.rule.pos.type = empty;
        end
        if (iOrientation == bottomLeft)
            insert.rule.pos = [iX - 1, iY + 1];
            insert.rule.pos.type = empty;
        end
    end
    return true;
end



nested function->bool IndexAt.IsFull()

    if (g:initIndexAt)
        return false;
    end

    insert.rule.pos = g:posIndexAt;
    insert.rule.pos.type = full;
    return true;
end



nested function->bool IndexAt.IsFullAt(array int aOrientations)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IndexAt.IsFullAt(array int " + aOrientations.name() + ") -> " + aOrientations.name() + " was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aOrientations.last)
            if (aOrientations[i] < top or aOrientations[i] > bottomLeft)
                error("IndexAt.IsFullAt(array int " + aOrientations.name() + ") -> values need to be top, right, bottom, left, topLeft, topRight, bottomRight or bottomLeft.");
            end
        end
    end
//

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
        if (iOrientation == bottomRight)
            insert.rule.pos = [iX + 1, iY + 1];
            insert.rule.pos.type = full;
        end
        if (iOrientation == bottomLeft)
            insert.rule.pos = [iX - 1, iY + 1];
            insert.rule.pos.type = full;
        end
    end
    return true;
end



nested function->bool IndexAt.IsOut()

    if (g:initIndexAt)
        return false;
    end

    insert.rule.pos = g:posIndexAt;
    insert.rule.pos.type = index;
    insert.rule.pos.index = -1;
    return true;
end



nested function->bool IndexAt.IsNotOut()

    if (g:initIndexAt)
        return false;
    end

    insert.rule.pos = g:posIndexAt;
    insert.rule.pos.type = notindex;
    insert.rule.pos.index = -1;
    return true;
end



nested function->bool IndexAt.IsWithinArea(int iWidth, int iHeight)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (iWidth < 1)
            error("IndexAt.IsWithinArea(int " + iWidth.name() + ", int " + iHeight.name() + ") -> " + iWidth.name() + " needs to be greater than 0.");
        end
        if (iHeight < 1)
            error("IndexAt.IsWithinArea(int " + iWidth.name() + ", int " + iHeight.name() + ") -> " + iHeight.name() + " needs to be greater than 0.");
        end
    end
//

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;
    
    for (x = iX to iX + iWidth - 1)
        for (y = iY to iY + iHeight - 1)            
            insert.rule.pos = [x, y];
            internal:TestIndicesFull();
            insert.rule.pos.operator = g:or;
            insert.rule.pos.group = g:group;
        end
    end
    
    g:group = g:group + 1;
    return true;
end



nested function->bool IndexAt.IsNotWithinArea(int iWidth, int iHeight)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (iWidth < 1)
            error("IndexAt.IsNotWithinArea(int " + iWidth.name() + ", int " + iHeight.name() + ") -> " + iWidth.name() + " needs to be greater than 0.");
        end
        if (iHeight < 1)
            error("IndexAt.IsNotWithinArea(int " + iWidth.name() + ", int " + iHeight.name() + ") -> " + iHeight.name() + " needs to be greater than 0.");
        end
    end
//

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;
    
    for (x = iX to iX + iWidth - 1)
        for (y = iY to iY + iHeight - 1)            
            insert.rule.pos = [x, y];
            internal:TestIndicesEmpty();
        end
    end
    return true;
end



nested function->bool IndexAt.IsWithinRadius(int iRadius)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (iRadius < 0)
            error("IndexAt.IsWithinRadius(int " + iRadius.name() + ") -> " + iRadius.name() + " needs to be greater than or equal to 0.");
        end
    end
//

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;
    
    for (x = util:Negate(iRadius) to iRadius)
        for (y = util:Negate(iRadius) to iRadius)
            int iDiffX = iX - x;
            int iDiffY = iY - y;
            
            if (iDiffX * iDiffX + iDiffY * iDiffY <= iRadius * iRadius)
                insert.rule.pos = [x, y];
                internal:TestIndicesFull();
                insert.rule.pos.operator = g:or;
                insert.rule.pos.group = g:group;
            end
        end
    end
    
    g:group = g:group + 1;
    return true;
end



nested function->bool IndexAt.IsNotWithinRadius(int iRadius)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (iRadius < 0)
            error("IndexAt.IsNotWithinRadius(int " + iRadius.name() + ") -> " + iRadius.name() + " needs to be greater than or equal to 0.");
        end
    end
//

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    for (x = util:Negate(iRadius) to iRadius)
        for (y = util:Negate(iRadius) to iRadius)
            int iDiffX = iX - x;
            int iDiffY = iY - y;
            
            if (iDiffX * iDiffX + iDiffY * iDiffY <= iRadius * iRadius)
                insert.rule.pos = [x, y];
                internal:TestIndicesEmpty();
            end
        end
    end
    return true;
end



nested function->bool IndexAt.IsEdge(int iOrientation)

    if (g:initIndexAt)
        return false;
    end
    
//
    if (s:debug)
        if (iOrientation < top or iOrientation > bottomLeft)
            error("IndexAt.IsEdge(int " + iOrientation.name() + ") -> value needs to be top, right, bottom, left, topLeft, topRight, bottomRight or bottomLeft.");
        end
    end
//

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
    if (iOrientation == bottomRight)
        insert.rule.pos = [iX, iY + 1];
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
    return true;
end



nested function->bool IndexAt.IsNotEdge(array int aOrientations)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IndexAt.IsNotEdge(array int " + aOrientations.name() + ") -> " + aOrientations.name() + " was empty, function had no effect.");
            return false;
        end
        
        for (i = 0 to aOrientations.last)
            if ((aOrientations[i] < top or aOrientations[i] > left) and aOrientations[i] != all)
                error("IndexAt.IsNotEdge(array int " + aOrientations.name() + ") -> values need to be top, right, bottom, left or all.");
            end
        end
    end
//

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    for (i = 0 to aOrientations.last)
        if (aOrientations[i] == top or aOrientations[i] == all)
            insert.rule.pos = [iX, iY - 1];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (aOrientations[i] == right or aOrientations[i] == all)
            insert.rule.pos = [iX + 1, iY];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (aOrientations[i] == bottom or aOrientations[i] == all)
            insert.rule.pos = [iX, iY + 1];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (aOrientations[i] == left or aOrientations[i] == all)
            insert.rule.pos = [iX - 1, iY];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
    end
    return true;
end



nested function->bool IndexAt.IsNextTo(array int aIndices)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("IndexAt.IsNextTo(array int " + aIndices.name() + ") -> " + aIndices.name() + " was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if ((aIndices[i] < -1 or aIndices[i] > 255) and aIndices[i] != this)
                error("IndexAt.IsNextTo(array int " + aIndices.name() + ") -> values need to be in range [-1-255].");
            end
        end
    end
//

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    for (i = 0 to aIndices.last)
        int iIndex = aIndices[i];

        insert.rule.pos = [iX - 1, iY];
        insert.rule.pos.type = index;
        if (iIndex != this) insert.rule.pos.index = iIndex; end
        if (iIndex == this) insert.rule.pos.index = g:vInsertIndex; end
        insert.rule.pos.operator = g:or;
        insert.rule.pos.group = g:group;

        insert.rule.pos = [iX, iY - 1];
        insert.rule.pos.type = index;
        if (iIndex != this) insert.rule.pos.index = iIndex; end
        if (iIndex == this) insert.rule.pos.index = g:vInsertIndex; end
        insert.rule.pos.operator = g:or;
        insert.rule.pos.group = g:group;

        insert.rule.pos = [iX + 1, iY];
        insert.rule.pos.type = index;
        if (iIndex != this) insert.rule.pos.index = iIndex; end
        if (iIndex == this) insert.rule.pos.index = g:vInsertIndex; end
        insert.rule.pos.operator = g:or;
        insert.rule.pos.group = g:group;

        insert.rule.pos = [iX, iY + 1];
        insert.rule.pos.type = index;
        if (iIndex != this) insert.rule.pos.index = iIndex; end
        if (iIndex == this) insert.rule.pos.index = g:vInsertIndex; end
        insert.rule.pos.operator = g:or;
        insert.rule.pos.group = g:group;
    end

    g:group = g:group + 1;
    return true;
end



nested function->bool IndexAt.IsNotNextTo(array int aIndices)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("IndexAt.IsNotNextTo(array int " + aIndices.name() + ") -> " + aIndices.name() + " was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if ((aIndices[i] < -1 or aIndices[i] > 255) and aIndices[i] != this)
                error("IndexAt.IsNotNextTo(array int " + aIndices.name() + ") -> values need to be in range [-1-255].");
            end
        end
    end
//

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    for (i = 0 to aIndices.last)
        int iIndex = aIndices[i];

        insert.rule.pos = [iX - 1, iY];
        insert.rule.pos.type = notindex;
        if (iIndex != this) insert.rule.pos.index = iIndex; end
        if (iIndex == this) insert.rule.pos.index = g:vInsertIndex; end

        insert.rule.pos = [iX, iY - 1];
        insert.rule.pos.type = notindex;
        if (iIndex != this) insert.rule.pos.index = iIndex; end
        if (iIndex == this) insert.rule.pos.index = g:vInsertIndex; end

        insert.rule.pos = [iX + 1, iY];
        insert.rule.pos.type = notindex;
        if (iIndex != this) insert.rule.pos.index = iIndex; end
        if (iIndex == this) insert.rule.pos.index = g:vInsertIndex; end

        insert.rule.pos = [iX, iY + 1];
        insert.rule.pos.type = notindex;
        if (iIndex != this) insert.rule.pos.index = iIndex; end
        if (iIndex == this) insert.rule.pos.index = g:vInsertIndex; end
    end
    return true;
end



nested function->bool IndexAt.IsWall(array int aOrientations)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IndexAt.IsWall(array int " + aOrientations.name() + ") -> " + aOrientations.name() + " was empty, function had no effect.");
            return false;
        end
        
        for (i = 0 to aOrientations.last)
            if (aOrientations[i] < top or aOrientations[i] > left)
                error("IndexAt.IsWall(array int " + aOrientations.name() + ") -> values need to be top, right, bottom or left.");
            end
        end
    end
//

    if (g:vTestIndices.count != 0)
        insert.rule.pos = g:posIndexAt;
        internal:TestIndicesFull();
    end

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
    return true;
end



nested function->bool IndexAt.IsOuterCorner(array int aOrientations)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IndexAt.IsOuterCorner(array int " + aOrientations.name() + ") -> " + aOrientations.name() + " was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aOrientations.last)
            if (aOrientations[i] < topLeft or aOrientations[i] > bottomLeft)
                error("IndexAt.IsOuterCorner(array int " + aOrientations.name() + ") -> values need to be topLeft, topRight, bottomRight or bottomLeft.");
            end
        end
    end
//

    if (g:vTestIndices.count != 0)
        insert.rule.pos = g:posIndexAt;
        internal:TestIndicesFull();
    end

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
    if (aOrientations.has(bottomRight))
        g:borderBottom = 0;
        g:borderRight = 0;
        g:borderTopRight = -1;
        g:borderBottomLeft = -1;
        g:borderBottomRight = -1;
    end
    if (aOrientations.has(bottomLeft))
        g:borderBottom = 0;
        g:borderLeft = 0;
        g:borderTopLeft = -1;
        g:borderBottomLeft = -1;
        g:borderBottomRight = -1;
    end
    return true;
end



nested function->bool IndexAt.IsInnerCorner(array int aOrientations)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("IndexAt.IsInnerCorner(array int " + aOrientations.name() + ") -> " + aOrientations.name() + " was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aOrientations.last)
            if (aOrientations[i] < topLeft or aOrientations[i] > bottomLeft)
                error("IndexAt.IsInnerCorner(array int " + aOrientations.name() + ") -> values need to be topLeft, topRight, bottomRight or bottomLeft.");
            end
        end
    end
//

    if (g:vTestIndices.count != 0)
        insert.rule.pos = g:posIndexAt;
        internal:TestIndicesFull();
    end

    if (aOrientations.has(topLeft))
        g:borderTopLeft = 0;
    end
    if (aOrientations.has(topRight))
        g:borderTopRight = 0;
    end
    if (aOrientations.has(bottomRight))
        g:borderBottomRight = 0;
    end
    if (aOrientations.has(bottomLeft))
        g:borderBottomLeft = 0;
    end
    return true;
end



nested function->bool IndexAt.HasSpaceFor(object oObject)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (oObject.count == 0)
            warning("IndexAt.HasSpaceFor(object " + oObject.name() + ") -> " + oObject.name() + " was empty, function had no effect.");
            return false;
        end
    end
//

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    for (i = 0 to oObject.last)
        coord cRelativePos = util:RelativePos(oObject.anchor, oObject[i]);

        insert.rule.pos = [cRelativePos.x + iX, cRelativePos.y + iY];
        internal:TestIndicesFull();
    end
    return true;
end



nested function->bool IndexAt.IsOverlapping(array object aObjects)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("IndexAt.IsOverlapping(array object " + aObjects.name() + ") -> " + aObjects.name() + " was empty, function had no effect.");
            return false;
        end
    end
//

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    for (i = 0 to aObjects.last)
        coord cAnchor = aObjects[i].anchor;

        for (j = 0 to aObjects[i].last)
            coord cRelativePos = util:RelativePos(cAnchor, aObjects[i][j]);

            insert.rule.pos = [iX + cRelativePos.x * -1, iY + cRelativePos.y * -1];
            insert.rule.pos.type = index;
            insert.rule.pos.index = cAnchor;
            insert.rule.pos.operator = g:or;
            insert.rule.pos.group = g:group;
        end
    end

    g:group = g:group + 1;
    return true;
end



nested function->bool IndexAt.IsNotOverlapping(array object aObjects)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("IndexAt.IsNotOverlapping(array object " + aObjects.name() + ") -> " + aObjects.name() + " was empty, function had no effect.");
            return false;
        end
    end
//

    int iX = g:posIndexAt.x;
    int iY = g:posIndexAt.y;

    for (i = 0 to aObjects.last)
        coord cAnchor = aObjects[i].anchor;

        for (j = 0 to aObjects[i].last)
            coord cRelativePos = util:RelativePos(cAnchor, aObjects[i][j]);

            insert.rule.pos = [iX + cRelativePos.x * -1, iY + cRelativePos.y * -1];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = cAnchor;
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
            error("Replace(int " + iFrom.name() + ", int " + iTo.name() + ") -> " + iFrom.name() + " needs to be in range [0-255].");
        end

        if (iTo < 0 or iTo > 255)
            error("Replace(int " + iFrom.name() + ", int " + iTo.name() + ") -> " + iTo.name() + " needs to be in range [0-255].");
        end
    end
//

    Insert(iTo).If(
        IndexAt(0).Is(iFrom)
    );
    invoke(nested);
end



nested function->null Replace.Chance(float fProbability)

//
    if (s:debug)
        if (fProbability <= 0)
            error("Replace.Chance(float " + fProbability.name() + ") -> " + fProbability.name() + " needs to be greater than 0.");
        end
    end
//

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
            error("ReplaceNot(int " + iNot.name() + ", int " + iTo.name() + ") -> " + iNot.name() + " needs to be in range [0-255].");
        end

        if (iTo < 0 or iTo > 255)
            error("ReplaceNot(int " + iNot.name() + ", int " + iTo.name() + ") -> " + iTo.name() + " needs to be in range [0-255].");
        end
    end
//

    Insert(iTo).If(
        IndexAt(0).IsNot(iNot)
    );
    invoke(nested);
end



nested function->null ReplaceNot.Chance(float fProbability)

//
    if (s:debug)
        if (fProbability <= 0)
            error("ReplaceNot.Chance(float " + fProbability.name() + ") -> " + fProbability.name() + " needs to be greater than 0.");
        end
    end
//

    util:Chance(fProbability);
end





///////////////////////////////////////
//
array object g:insertedObjects;
/******************************************************************************

*/
function->null InsertObject(array object aObjects)
    nested(
        At,
        NoDefaultPosRule, Chance, Roll, If
    )

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("InsertObject(array object " + aObjects.name() + ") -> " + aObjects.name() + " was empty, function had no effect.");
            return;
        end
    end
//

    invoke(nested);
    g:initInsert = false;

    internal:UpdateProbabilities(aObjects.last);
    if (g:roll or g:randomize)
        insert.nocopy;
    end

    for (i = 0 to aObjects.last)
        g:vInsertObject = aObjects[i];
        g:vInsertIndex = aObjects[i].anchor;

        if (not g:insertedObjects.has(g:vInsertObject))
            g:insertedObjects.push(g:vInsertObject);
        end

        insert.newrule;
        util:InsertIndex(g:vInsertIndex);
        util:Chance(g:argInsertChance[g:argInsertChanceIndex]);

        invoke(nested);

        g:argInsertChanceIndex = g:argInsertChanceIndex + 1;
    end

    array float aEmpty;
    g:argInsertChance = aEmpty;
    g:argInsertChanceIndex = 0;

    internal:InsertResetFlags();
    internal:ResetFlags();
end



nested function->null InsertObject.At(coord cPos)

    if (g:initInsert)
        g:hasAt = true;
        return;
    end

//
    if (s:debug)
        if (cPos.x < 0)
            warning("InsertObject.At(coord " + cPos.name() + ") -> " + cPos.name() + ".x was negative, function had no effect.");
            return;
        end
        if (cPos.y < 0)
            warning("InsertObject.At(coord " + cPos.name() + ") -> " + cPos.name() + ".y was negative, function had no effect.");
            return;
        end
    end
//

    coord cPosNegated = util:Negate(cPos);

    insert.rule.pos = cPosNegated;
    insert.rule.pos.type = notindex;
    insert.rule.pos.index = -1;

    insert.rule.pos = [cPosNegated.x - 1, 0];
    insert.rule.pos.type = index;
    insert.rule.pos.index = -1;

    insert.rule.pos = [0, cPosNegated.y - 1];
    insert.rule.pos.type = index;
    insert.rule.pos.index = -1;

    insert.rule.nodefault;
end



nested function->null InsertObject.NoDefaultPosRule()

    if (g:initInsert)
        return;
    end
    insert.rule.nodefault;
end



nested function->null InsertObject.Chance(array float aProbabilities)

//
    if (s:debug)
        if (aProbabilities.count == 0)
            warning("InsertObject.Chance(array float " + aProbabilities.name() + ") -> " + aProbabilities.name() + " was empty, function had no effect.");
            return;
        end

        for (i = 0 to aProbabilities.last)
            if (aProbabilities[i] <= 0)
                error("InsertObject.Chance(array float " + aProbabilities.name() + ") -> values need to be greater than 0.");
            end
        end
    end
//

    if (g:initInsert)
        g:randomize = true;
        g:argInsertChance = aProbabilities;
        return;
    end
end



nested function->null InsertObject.Roll()

    if (g:initInsert)
        g:roll = true;
        return;
    end
end



nested function->null InsertObject.If(array bool bTests)
end



///////////////////////////////////////
//
bool g:initObject = true;

int g:vObjectTop    = 0;
int g:vObjectRight  = 0;
int g:vObjectBottom = 0;
int g:vObjectLeft   = 0;
/******************************************************************************

*/
function->null internal:ObjectResetFlags()

    g:initObject = true;
end



function->bool Object()
    nested(
        TestIndices,
        HasSpace, Fits, IsOver,
        IsTouchingObjectAt, IsTouchingWallAt,
        IsEdge, IsNotEdge,
        IsNextTo, IsNotNextTo,
        IsOverlapping, IsNotOverlapping
    )

    if (g:initInsert or g:hasAt)
        return false;
    end

    invoke(nested);
    g:initObject = false;

    insert.nocopy;

    array int aRect = util:Rect(g:vInsertObject);
    g:vObjectTop    = aRect[0];
    g:vObjectRight  = aRect[1];
    g:vObjectBottom = aRect[2];
    g:vObjectLeft   = aRect[3];

    invoke(nested);

    array int aEmpty;
    g:vTestIndices = aEmpty;

    internal:ObjectResetFlags();
    internal:ResetFlags();
    return true;
end



nested function->bool Object.TestIndices(array int aIndices)

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("InsertObject.TestIndices(array int " + aIndices.name() + ") -> " + aIndices.name() + " was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < 0 or aIndices[i] > 255)
                error("InsertObject.TestIndices(array int " + aIndices.name() + ") -> values need to be in range [0-255].");
            end
        end
    end
//

    if (g:initObject)
        g:vTestIndices = aIndices;
        return false;
    end
    return true;
end



nested function->bool Object.HasSpace()

    if (g:initObject)
        return false;
    end

    object oObject = g:vInsertObject;
    coord cAnchor = g:vInsertIndex;

    for (i = 0 to oObject.last)
        insert.rule.pos = util:RelativePos(cAnchor, oObject[i]);
        internal:TestIndicesFull();
    end
    return true;
end



nested function->bool Object.Fits()

    if (g:initObject)
        return false;
    end

    object oObject = g:vInsertObject;
    coord cAnchor = g:vInsertIndex;

    array coord aRelativePos;
    for (i = 0 to oObject.last)
        coord cRelativePos = util:RelativePos(cAnchor, oObject[i]);

        aRelativePos.push(cRelativePos);

        insert.rule.pos = cRelativePos;
        internal:TestIndicesFull();
    end

    for (i = 0 to aRelativePos.last)
        coord cPos = aRelativePos[i];

        coord cTop    = [cPos.x, cPos.y - 1];
        coord cRight  = [cPos.x + 1, cPos.y];
        coord cBottom = [cPos.x, cPos.y + 1];
        coord cLeft   = [cPos.x - 1, cPos.y];

        if (not aRelativePos.has(cTop))
            insert.rule.pos = cTop;
            internal:TestIndicesEmpty();
        end
        if (not aRelativePos.has(cRight))
            insert.rule.pos = cRight;
            internal:TestIndicesEmpty();
        end
        if (not aRelativePos.has(cBottom))
            insert.rule.pos = cBottom;
            internal:TestIndicesEmpty();
        end
        if (not aRelativePos.has(cLeft))
            insert.rule.pos = cLeft;
            internal:TestIndicesEmpty();
        end
    end
    return true;
end



nested function->bool Object.IsOver(array object aObjects)

    if (g:initObject)
        return false;
    end

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("Object.IsOver(array object " + aObjects.name() + ") -> " + aObjects.name() + " was empty, function had no effect.");
            return false;
        end
    end
//

    insert.rule.pos = [0, 0];
    for (i = 0 to aObjects.last)
        insert.rule.pos.type = index;
        insert.rule.pos.index = aObjects[i].anchor;
    end
    return true;
end



nested function->bool Object.IsTouchingObjectAt(object oObject, int iSide)

    if (g:initObject)
        return false;
    end

//
    if (s:debug)
        if (oObject.count == 0)
            warning("Object.IsTouchingObjectAt(object " + oObject.name() + ", int " + iSide.name() + ") -> " + oObject.name() + " was empty, function had no effect.");
            return false;
        end
        if (iSide < top or iSide > left)
            error("Object.IsTouchingObjectAt(object " + oObject.name() + ", int " + iSide.name() + ") -> " + iSide.name() + " needs to be top, right, bottom or left.");
        end
    end
//

    array coord aFootprintPos = Footprint(g:vInsertObject, iSide);

    array int aFootprintX;
    array int aFootprintY;
    array int aDistanceX;
    array int aDistanceY;
    for (i = 0 to aFootprintPos.last)
        aFootprintX.push(aFootprintPos[i].x);
        aFootprintY.push(aFootprintPos[i].y);
        if (i > 0)
            aDistanceX.push(aFootprintPos[i].x - aFootprintPos[i - 1].x);
            aDistanceY.push(aFootprintPos[i].y - aFootprintPos[i - 1].y);
        end
    end

    array coord aOtherFootprintPos = Footprint(oObject, util:OppositeSide(iSide));

    if (aFootprintPos.count <= aOtherFootprintPos.count)
        array int aOtherFootprintX;
        array int aOtherFootprintY;
        array int aOtherDistanceX;
        array int aOtherDistanceY;
        for (j = 0 to aOtherFootprintPos.last)
            aOtherFootprintX.push(aOtherFootprintPos[j].x);
            aOtherFootprintY.push(aOtherFootprintPos[j].y);
            if (j > 0)
                aOtherDistanceX.push(aOtherFootprintPos[j].x - aOtherFootprintPos[j - 1].x);
                aOtherDistanceY.push(aOtherFootprintPos[j].y - aOtherFootprintPos[j - 1].y);
            end
        end
        
        int iMatchIndex = 0;
        if (iSide == top or iSide == bottom)
            iMatchIndex = aOtherDistanceX.find(aDistanceX);
        end
        if (iSide == left or iSide == right)
            iMatchIndex = aOtherDistanceY.find(aDistanceY);
        end

        if (util:Found(iMatchIndex))
            if (iSide == top)
                insert.rule.pos = [aFootprintX[0] - aOtherFootprintX[0], util:Negate(aOtherFootprintPos[0].y)];
            end
            if (iSide == bottom)
                insert.rule.pos = [aFootprintX[0] - aOtherFootprintX[0], aFootprintPos[0].y];
            end
            if (iSide == left)
                insert.rule.pos = [util:Negate(aOtherFootprintPos[0].x), aFootprintY[0] - aOtherFootprintY[0]];
            end
            if (iSide == right)
                insert.rule.pos = [aFootprintPos[0].x, aFootprintY[0] - aOtherFootprintY[0]];
            end
            insert.rule.pos.type = index;
            insert.rule.pos.index = oObject.anchor;

            return true;
        end
    end

//
    if (s:debug)
        warning("Object.IsTouchingObjectAt(object " + oObject.name() + ", int " + iSide.name() + ") -> matching footprint was not found, function had no effect.");
    end
//
    return false;
end



nested function->bool Object.IsTouchingWallAt(int iSide)

    if (g:initObject)
        return false;
    end
    
//
    if (s:debug)
        if (iSide < top or iSide > left)
            error("Object.IsTouchingWallAt(int " + iSide.name() + ") -> value needs to be top, right, bottom or left.");
        end
    end
//

    object oObject = g:vInsertObject;

    array coord aFootprintPos = Footprint(oObject, iSide);
    for (i = 0 to aFootprintPos.last)
        insert.rule.pos = aFootprintPos[i];
        internal:TestIndicesFull();
    end
    return true;
end



nested function->bool Object.IsEdge(int iOrientation)

    if (g:initObject)
        return false;
    end
    
//
    if (s:debug)
        if (iOrientation < top or iOrientation > bottomLeft)
            error("Object.IsEdge(int " + iOrientation.name() + ") -> value needs to be top, right, bottom, left, topLeft, topRight, bottomRight or bottomLeft.");
        end
    end
//

    if (iOrientation == top)
        insert.rule.pos = [0, g:vObjectTop - 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        return true;
    end
    if (iOrientation == right)
        insert.rule.pos = [g:vObjectRight + 1, 0];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        return true;
    end
    if (iOrientation == bottom)
        insert.rule.pos = [0, g:vObjectBottom + 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        return true;
    end
    if (iOrientation == left)
        insert.rule.pos = [g:vObjectLeft - 1, 0];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        return true;
    end
    if (iOrientation == topLeft)
        insert.rule.pos = [0, g:vObjectTop - 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        insert.rule.pos = [g:vObjectLeft - 1, 0];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        return true;
    end
    if (iOrientation == topRight)
        insert.rule.pos = [0, g:vObjectTop - 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        insert.rule.pos = [g:vObjectRight + 1, 0];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        return true;
    end
    if (iOrientation == bottomRight)
        insert.rule.pos = [0, g:vObjectBottom + 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        insert.rule.pos = [g:vObjectRight + 1, 0];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        return true;
    end
    if (iOrientation == bottomLeft)
        insert.rule.pos = [0, g:vObjectBottom + 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        insert.rule.pos = [g:vObjectLeft - 1, 0];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        return true;
    end
    return true;
end



nested function->bool Object.IsNotEdge(array int aOrientations)

    if (g:initObject)
        return false;
    end

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("Object.IsNotEdge(array int " + aOrientations.name() + ") -> " + aOrientations.name() + " was empty, function had no effect.");
            return false;
        end
        
        for (i = 0 to aOrientations.last)
            if ((aOrientations[i] < top or aOrientations[i] > left) and aOrientations[i] != all)
                error("Object.IsNotEdge(array int " + aOrientations.name() + ") -> values need to be top, right, bottom, left or all.");
            end
        end
    end
//

    for (i = 0 to aOrientations.last)
        if (aOrientations[i] == top or aOrientations[i] == all)
            insert.rule.pos = [0, g:vObjectTop - 1];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (aOrientations[i] == right or aOrientations[i] == all)
            insert.rule.pos = [g:vObjectRight + 1, 0];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (aOrientations[i] == bottom or aOrientations[i] == all)
            insert.rule.pos = [0, g:vObjectBottom + 1];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (aOrientations[i] == left or aOrientations[i] == all)
            insert.rule.pos = [g:vObjectLeft - 1, 0];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
    end
    return true;
end



nested function->bool Object.IsNextTo(array object aObjects)

    if (g:initObject)
        return false;
    end

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("Object.IsNextTo(array object " + aObjects.name() + ") -> " + aObjects.name() + " was empty, function had no effect.");
            return false;
        end
    end
//

    object oObject = g:vInsertObject;
    coord cAnchor = g:vInsertIndex;

    array coord aNextToPos;
    for (i = 0 to aObjects.last)
        coord cOtherAnchor = aObjects[i].anchor;

        array coord aPos;
        for (j = 0 to aObjects[i].last)
            coord cOtherRelativePos = util:RelativePos(cOtherAnchor, aObjects[i][j]);

            for (k = 0 to oObject.last)
                coord cRelativePos = util:RelativePos(cAnchor, oObject[k]);

                coord cPos1 = [cRelativePos.x - cOtherRelativePos.x - 1, cRelativePos.y - cOtherRelativePos.y];
                coord cPos2 = [cRelativePos.x - cOtherRelativePos.x + 1, cRelativePos.y - cOtherRelativePos.y];
                coord cPos3 = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y - 1];
                coord cPos4 = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y + 1];

                if (not aNextToPos.has(cPos1))
                    aNextToPos.push(cPos1);
                end
                if (not aNextToPos.has(cPos2))
                    aNextToPos.push(cPos2);
                end
                if (not aNextToPos.has(cPos3))
                    aNextToPos.push(cPos3);
                end
                if (not aNextToPos.has(cPos4))
                    aNextToPos.push(cPos4);
                end
            end
        end
    end

    for (n = 0 to aNextToPos.last)
        for (i = 0 to aObjects.last)
            coord cOtherAnchor = aObjects[i].anchor;

            insert.rule.pos = aNextToPos[n];
            insert.rule.pos.type = index;
            insert.rule.pos.index = cOtherAnchor;
            insert.rule.pos.operator = g:or;
            insert.rule.pos.group = g:group;

            array coord aPos;
            for (j = 0 to aObjects[i].last)
                coord cOtherRelativePos = util:RelativePos(cOtherAnchor, aObjects[i][j]);

                for (k = 0 to oObject.last)
                    coord cRelativePos = util:RelativePos(cAnchor, oObject[k]);

                    coord cPos = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y];
                    if (not aPos.has(cPos))
                        aPos.push(cPos);

                        insert.rule.pos = cPos;
                        insert.rule.pos.type = notindex;
                        insert.rule.pos.index = cOtherAnchor;
                    end
                end
            end
        end
    end

    g:group = g:group + 1;
    return true;
end



nested function->bool Object.IsNotNextTo(array object aObjects)

    if (g:initObject)
        return false;
    end

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("Object.IsNotNextTo(array object " + aObjects.name() + ") -> " + aObjects.name() + " was empty, function had no effect.");
            return false;
        end
    end
//

    object oObject = g:vInsertObject;
    coord cAnchor = g:vInsertIndex;

    for (i = 0 to aObjects.last)
        coord cOtherAnchor = aObjects[i].anchor;

        array coord aPos;
        for (j = 0 to aObjects[i].last)
            coord cOtherRelativePos = util:RelativePos(cOtherAnchor, aObjects[i][j]);

            for (k = 0 to oObject.last)
                coord cRelativePos = util:RelativePos(cAnchor, oObject[k]);

                coord cPos = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y];
                if (not aPos.has(cPos))
                    aPos.push(cPos);

                    insert.rule.pos = cPos;
                    insert.rule.pos.type = notindex;
                    insert.rule.pos.index = cOtherAnchor;
                end

                insert.rule.pos = [cRelativePos.x - cOtherRelativePos.x - 1, cRelativePos.y - cOtherRelativePos.y];
                insert.rule.pos.type = notindex;
                insert.rule.pos.index = cOtherAnchor;

                insert.rule.pos = [cRelativePos.x - cOtherRelativePos.x + 1, cRelativePos.y - cOtherRelativePos.y];
                insert.rule.pos.type = notindex;
                insert.rule.pos.index = cOtherAnchor;

                insert.rule.pos = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y - 1];
                insert.rule.pos.type = notindex;
                insert.rule.pos.index = cOtherAnchor;

                insert.rule.pos = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y + 1];
                insert.rule.pos.type = notindex;
                insert.rule.pos.index = cOtherAnchor;
            end
        end
    end
    return true;
end



nested function->bool Object.IsOverlapping(array object aObjects)

    if (g:initObject)
        return false;
    end

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("Object.IsOverlapping(array object " + aObjects.name() + ") -> " + aObjects.name() + " was empty, function had no effect.");
            return false;
        end
    end
//

    object oObject = g:vInsertObject;
    coord cAnchor = g:vInsertIndex;

    for (i = 0 to aObjects.last)
        coord cOtherAnchor = aObjects[i].anchor;

        array coord aPos;
        for (j = 0 to aObjects[i].last)
            coord cOtherRelativePos = util:RelativePos(cOtherAnchor, aObjects[i][j]);

            for (k = 0 to oObject.last)
                coord cRelativePos = util:RelativePos(cAnchor, oObject[k]);

                coord cPos = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y];
                if (not aPos.has(cPos))
                    aPos.push(cPos);

                    insert.rule.pos = cPos;
                    insert.rule.pos.type = index;
                    insert.rule.pos.index = cOtherAnchor;
                    insert.rule.pos.operator = g:or;
                    insert.rule.pos.group = g:group;
                end
            end
        end
    end

    g:group = g:group + 1;
    return true;
end



nested function->bool Object.IsNotOverlapping(array object aObjects)

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("Object.IsNotOverlapping(array object " + aObjects.name() + ") -> " + aObjects.name() + " was empty, function had no effect.");
            return false;
        end
    end
//

    object oObject = g:vInsertObject;
    coord cAnchor = g:vInsertIndex;

    for (i = 0 to aObjects.last)
        coord cOtherAnchor = aObjects[i].anchor;

        array coord aPos;
        for (j = 0 to aObjects[i].last)
            coord cOtherRelativePos = util:RelativePos(cOtherAnchor, aObjects[i][j]);

            for (k = 0 to oObject.last)
                coord cRelativePos = util:RelativePos(cAnchor, oObject[k]);

                coord cPos = [cRelativePos.x - cOtherRelativePos.x, cRelativePos.y - cOtherRelativePos.y];
                if (not aPos.has(cPos))
                    aPos.push(cPos);

                    insert.rule.pos = cPos;
                    insert.rule.pos.type = notindex;
                    insert.rule.pos.index = cOtherAnchor;
                end
            end
        end
    end
    return true;
end





///////////////////////////////////////
//
array int g:argFilterIndices;
/******************************************************************************

*/
function->null internal:ResetFilterArgs()

    array int aEmpty;
    g:argFilterIndices = aEmpty;
end



function->null Filter()
    nested(
        SetIndices
    )

    invoke(nested);
end



nested function->null Filter.SetIndices(array int aIndices)

    g:argFilterIndices = aIndices;
end





///////////////////////////////////////
//
array int g:argShiftIndices;
coord g:argShiftOffset = [0, 0];
/******************************************************************************

*/
function->null internal:ResetShiftArgs()

    array int aEmpty;
    g:argShiftIndices = aEmpty;
end



function->null Shift()
    nested(
        SetIndices, SetOffset
    )

    invoke(nested);
end



nested function->null Shift.SetIndices(array int aIndices)

    g:argShiftIndices = aIndices;
end



nested function->null Shift.SetOffset(coord cOffset)

    g:argShiftOffset = cOffset;
end





///////////////////////////////////////
//
coord g:argCheckerboardSize = [1, 1];
int g:argCheckerboardIndex1 = g:mask.N;
int g:argCheckerboardIndex2 = g:mask.V;
/******************************************************************************

*/
function->null internal:ResetCheckerboardArgs()

    g:argCheckerboardSize = [1, 1];
    g:argCheckerboardIndex1 = g:mask.N;
    g:argCheckerboardIndex2 = g:mask.V;
end



function->null Checkerboard()
    nested(
        SetSize, SetIndices
    )

    invoke(nested);
end



nested function->null Checkerboard.SetSize(coord cSize)

//
    if (s:debug)
        if (cSize.x < 1 or cSize.y < 1)
            error("Checkerboard.SetSize(coord " + cSize.name() + ") -> " + cSize.name() + " needs to be greater than 0.");
        end
    end
//

    g:argCheckerboardSize = cSize;
end



nested function->null Checkerboard.SetIndices(int iIndex1, int iIndex2)

//
    if (s:debug)
        if (iIndex1 < 0 or iIndex1 > 255)
            error("Checkerboard.SetIndices(int " + iIndex1.name() + ", " + iIndex2.name() + ") -> " + iIndex1.name() + " needs to be in range [0-255].");
        end
        if (iIndex2 < 0 or iIndex2 > 255)
            error("Checkerboard.SetIndices(int " + iIndex1.name() + ", " + iIndex2.name() + ") -> " + iIndex2.name() + " needs to be in range [0-255].");
        end
    end
//

    g:argCheckerboardIndex1 = iIndex1;
    g:argCheckerboardIndex2 = iIndex2;
end





///////////////////////////////////////
//
int g:argBorderWall:t = -1;
int g:argBorderWall:r = -1;
int g:argBorderWall:b = -1;
int g:argBorderWall:l = -1;
int g:argBorderOuter:tl = -1;
int g:argBorderOuter:tr = -1;
int g:argBorderOuter:br = -1;
int g:argBorderOuter:bl = -1;
int g:argBorderInner:tl = -1;
int g:argBorderInner:tr = -1;
int g:argBorderInner:br = -1;
int g:argBorderInner:bl = -1;
int g:argBorderDiagonal:tl = -1;
int g:argBorderDiagonal:tr = -1;
int g:argBorderIShape:v = -1;
int g:argBorderIShape:h = -1;
int g:argBorderUShape:t = -1;
int g:argBorderUShape:r = -1;
int g:argBorderUShape:b = -1;
int g:argBorderUShape:l = -1;
int g:argBorderLShape:tl = -1;
int g:argBorderLShape:tr = -1;
int g:argBorderLShape:br = -1;
int g:argBorderLShape:bl = -1;
int g:argBorderTShape:t = -1;
int g:argBorderTShape:r = -1;
int g:argBorderTShape:b = -1;
int g:argBorderTShape:l = -1;
int g:argBorderWallToIShape:t = -1;
int g:argBorderWallToIShape:r = -1;
int g:argBorderWallToIShape:b = -1;
int g:argBorderWallToIShape:l = -1;
int g:argBorderOuterToIShape:tl:v = -1;
int g:argBorderOuterToIShape:tr:v = -1;
int g:argBorderOuterToIShape:br:v = -1;
int g:argBorderOuterToIShape:bl:v = -1;
int g:argBorderOuterToIShape:tl:h = -1;
int g:argBorderOuterToIShape:tr:h = -1;
int g:argBorderOuterToIShape:br:h = -1;
int g:argBorderOuterToIShape:bl:h = -1;
int g:argBorderOuterToDoubleIShape:tl = -1;
int g:argBorderOuterToDoubleIShape:tr = -1;
int g:argBorderOuterToDoubleIShape:br = -1;
int g:argBorderOuterToDoubleIShape:bl = -1;
int g:argBorderCross = -1;
int g:argBorderDot = -1;
int g:argBorderFill = -1;
array int g:argBorderTestIndices;
/******************************************************************************

*/
function->null internal:ResetBorderArgs()

    g:argBorderWall:t = -1;
    g:argBorderWall:r = -1;
    g:argBorderWall:b = -1;
    g:argBorderWall:l = -1;
    g:argBorderOuter:tl = -1;
    g:argBorderOuter:tr = -1;
    g:argBorderOuter:br = -1;
    g:argBorderOuter:bl = -1;
    g:argBorderInner:tl = -1;
    g:argBorderInner:tr = -1;
    g:argBorderInner:br = -1;
    g:argBorderInner:bl = -1;
    g:argBorderDiagonal:tl = -1;
    g:argBorderDiagonal:tr = -1;
    g:argBorderIShape:v = -1;
    g:argBorderIShape:h = -1;
    g:argBorderUShape:t = -1;
    g:argBorderUShape:r = -1;
    g:argBorderUShape:b = -1;
    g:argBorderUShape:l = -1;
    g:argBorderLShape:tl = -1;
    g:argBorderLShape:tr = -1;
    g:argBorderLShape:br = -1;
    g:argBorderLShape:bl = -1;
    g:argBorderTShape:t = -1;
    g:argBorderTShape:r = -1;
    g:argBorderTShape:b = -1;
    g:argBorderTShape:l = -1;
    g:argBorderWallToIShape:t = -1;
    g:argBorderWallToIShape:r = -1;
    g:argBorderWallToIShape:b = -1;
    g:argBorderWallToIShape:l = -1;
    g:argBorderOuterToIShape:tl:v = -1;
    g:argBorderOuterToIShape:tr:v = -1;
    g:argBorderOuterToIShape:br:v = -1;
    g:argBorderOuterToIShape:bl:v = -1;
    g:argBorderOuterToIShape:tl:h = -1;
    g:argBorderOuterToIShape:tr:h = -1;
    g:argBorderOuterToIShape:br:h = -1;
    g:argBorderOuterToIShape:bl:h = -1;
    g:argBorderOuterToDoubleIShape:tl = -1;
    g:argBorderOuterToDoubleIShape:tr = -1;
    g:argBorderOuterToDoubleIShape:br = -1;
    g:argBorderOuterToDoubleIShape:bl = -1;
    g:argBorderCross = -1;
    g:argBorderDot = -1;
    g:argBorderFill = -1;

    array int aEmpty;
    g:argBorderTestIndices = aEmpty;
end



function->null Border()
    nested(
        SetWall, SetWallFrom,
        SetOuter, SetOuterFrom,
        SetInner, SetInnerFrom,
        SetDiagonal, SetDiagonalFrom,
        SetIShape, SetIShapeFrom,
        SetUShape, SetUShapeFrom,
        SetLShape, SetLShapeFrom,
        SetTShape, SetTShapeFrom,
        SetWallToIShape, SetWallToIShapeFrom,
        SetOuterToIShape, SetOuterToIShapeFrom,
        SetOuterToDoubleIShape, SetOuterToDoubleIShapeFrom,
        SetCross, SetDot, SetFill, 
        SetTestIndices
    )

    invoke(nested);
end



nested function->null Border.SetWall(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < top or iOrientation > left)
            error("Border.SetWall(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be top, right, bottom or left.");
        end
    end
//

    if (iOrientation == top)
        g:argBorderWall:t = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == right)
        g:argBorderWall:r = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == bottom)
        g:argBorderWall:b = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == left)
        g:argBorderWall:l = util:EnsureRotation(iIndex);
        return;
    end
end



nested function->null Border.SetWallFrom(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < top or iOrientation > left)
            error("Border.SetWallFrom(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be top, right, bottom or left.");
        end
    end
//

    if (iOrientation == top)
        g:argBorderWall:t = util:EnsureRotation(iIndex);
        g:argBorderWall:r = util:Rotate(g:argBorderWall:t);
        g:argBorderWall:b = util:Rotate(g:argBorderWall:r);
        g:argBorderWall:l = util:Rotate(g:argBorderWall:b);
        return;
    end
    if (iOrientation == right)
        g:argBorderWall:r = util:EnsureRotation(iIndex);
        g:argBorderWall:b = util:Rotate(g:argBorderWall:r);
        g:argBorderWall:l = util:Rotate(g:argBorderWall:b);
        g:argBorderWall:t = util:Rotate(g:argBorderWall:l);
        return;
    end
    if (iOrientation == bottom)
        g:argBorderWall:b = util:EnsureRotation(iIndex);
        g:argBorderWall:l = util:Rotate(g:argBorderWall:b);
        g:argBorderWall:t = util:Rotate(g:argBorderWall:l);
        g:argBorderWall:r = util:Rotate(g:argBorderWall:t);
        return;
    end
    if (iOrientation == left)
        g:argBorderWall:l = util:EnsureRotation(iIndex);
        g:argBorderWall:t = util:Rotate(g:argBorderWall:l);
        g:argBorderWall:r = util:Rotate(g:argBorderWall:t);
        g:argBorderWall:b = util:Rotate(g:argBorderWall:r);
        return;
    end
end



nested function->null Border.SetOuter(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < topLeft or iOrientation > bottomLeft)
            error("Border.SetOuter(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be topLeft, topRight, bottomRight or bottomLeft.");
        end
    end
//

    if (iOrientation == topLeft)
        g:argBorderOuter:tl = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == topRight)
        g:argBorderOuter:tr = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == bottomRight)
        g:argBorderOuter:br = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == bottomLeft)
        g:argBorderOuter:bl = util:EnsureRotation(iIndex);
        return;
    end
end



nested function->null Border.SetOuterFrom(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < topLeft or iOrientation > bottomLeft)
            error("Border.SetOuterFrom(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be topLeft, topRight, bottomRight or bottomLeft.");
        end
    end
//

    if (iOrientation == topLeft)
        g:argBorderOuter:tl = util:EnsureRotation(iIndex);
        g:argBorderOuter:tr = util:Rotate(g:argBorderOuter:tl);
        g:argBorderOuter:br = util:Rotate(g:argBorderOuter:tr);
        g:argBorderOuter:bl = util:Rotate(g:argBorderOuter:br);
        return;
    end
    if (iOrientation == topRight)
        g:argBorderOuter:tr = util:EnsureRotation(iIndex);
        g:argBorderOuter:br = util:Rotate(g:argBorderOuter:tr);
        g:argBorderOuter:bl = util:Rotate(g:argBorderOuter:br);
        g:argBorderOuter:tl = util:Rotate(g:argBorderOuter:bl);
        return;
    end
    if (iOrientation == bottomRight)
        g:argBorderOuter:br = util:EnsureRotation(iIndex);
        g:argBorderOuter:bl = util:Rotate(g:argBorderOuter:br);
        g:argBorderOuter:tl = util:Rotate(g:argBorderOuter:bl);
        g:argBorderOuter:tr = util:Rotate(g:argBorderOuter:tl);
        return;
    end
    if (iOrientation == bottomLeft)
        g:argBorderOuter:bl = util:EnsureRotation(iIndex);
        g:argBorderOuter:tl = util:Rotate(g:argBorderOuter:bl);
        g:argBorderOuter:tr = util:Rotate(g:argBorderOuter:tl);
        g:argBorderOuter:br = util:Rotate(g:argBorderOuter:tr);
        return;
    end
end



nested function->null Border.SetInner(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < topLeft or iOrientation > bottomLeft)
            error("Border.SetInner(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be topLeft, topRight, bottomRight or bottomLeft.");
        end
    end
//

    if (iOrientation == topLeft)
        g:argBorderInner:tl = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == topRight)
        g:argBorderInner:tr = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == bottomRight)
        g:argBorderInner:br = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == bottomLeft)
        g:argBorderInner:bl = util:EnsureRotation(iIndex);
        return;
    end
end



nested function->null Border.SetInnerFrom(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < topLeft or iOrientation > bottomLeft)
            error("Border.SetInnerFrom(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be topLeft, topRight, bottomRight or bottomLeft.");
        end
    end
//

    if (iOrientation == topLeft)
        g:argBorderInner:tl = util:EnsureRotation(iIndex);
        g:argBorderInner:tr = util:Rotate(g:argBorderInner:tl);
        g:argBorderInner:br = util:Rotate(g:argBorderInner:tr);
        g:argBorderInner:bl = util:Rotate(g:argBorderInner:br);
        return;
    end
    if (iOrientation == topRight)
        g:argBorderInner:tr = util:EnsureRotation(iIndex);
        g:argBorderInner:br = util:Rotate(g:argBorderInner:tr);
        g:argBorderInner:bl = util:Rotate(g:argBorderInner:br);
        g:argBorderInner:tl = util:Rotate(g:argBorderInner:bl);
        return;
    end
    if (iOrientation == bottomRight)
        g:argBorderInner:br = util:EnsureRotation(iIndex);
        g:argBorderInner:bl = util:Rotate(g:argBorderInner:br);
        g:argBorderInner:tl = util:Rotate(g:argBorderInner:bl);
        g:argBorderInner:tr = util:Rotate(g:argBorderInner:tl);
        return;
    end
    if (iOrientation == bottomLeft)
        g:argBorderInner:bl = util:EnsureRotation(iIndex);
        g:argBorderInner:tl = util:Rotate(g:argBorderInner:bl);
        g:argBorderInner:tr = util:Rotate(g:argBorderInner:tl);
        g:argBorderInner:br = util:Rotate(g:argBorderInner:tr);
        return;
    end
end



nested function->null Border.SetDiagonal(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < topLeft or iOrientation > bottomLeft)
            error("Border.SetDiagonal(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be topLeft, topRight, bottomRight or bottomLeft.");
        end
    end
//

    if (iOrientation == topLeft or iOrientation == bottomRight)
        g:argBorderDiagonal:tl = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == topRight or iOrientation == bottomLeft)
        g:argBorderDiagonal:tr = util:EnsureRotation(iIndex);
        return;
    end
end



nested function->null Border.SetDiagonalFrom(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < topLeft or iOrientation > bottomLeft)
            error("Border.SetDiagonalFrom(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be topLeft, topRight, bottomRight or bottomLeft.");
        end
    end
//

    if (iOrientation == topLeft or iOrientation == bottomRight)
        g:argBorderDiagonal:tl = util:EnsureRotation(iIndex);
        g:argBorderDiagonal:tr = util:Rotate(g:argBorderDiagonal:tl);
        return;
    end
    if (iOrientation == topRight or iOrientation == bottomLeft)
        g:argBorderDiagonal:tr = util:EnsureRotation(iIndex);
        g:argBorderDiagonal:tl = util:Rotate(g:argBorderDiagonal:tr);
        return;
    end
end



nested function->null Border.SetIShape(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation != vertical and iOrientation != horizontal)
            error("Border.SetIShape(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be vertical or horizontal.");
        end
    end
//

    if (iOrientation == vertical)
        g:argBorderIShape:v = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == horizontal)
        g:argBorderIShape:h = util:EnsureRotation(iIndex);
        return;
    end
end



nested function->null Border.SetIShapeFrom(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation != vertical and iOrientation != horizontal)
            error("Border.SetIShapeFrom(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be vertical or horizontal.");
        end
    end
//

    if (iOrientation == vertical)
        g:argBorderIShape:v = util:EnsureRotation(iIndex);
        g:argBorderIShape:h = util:Rotate(g:argBorderIShape:v);
        return;
    end
    if (iOrientation == horizontal)
        g:argBorderIShape:h = util:EnsureRotation(iIndex);
        g:argBorderIShape:v = util:Rotate(g:argBorderIShape:h);
        return;
    end
end



nested function->null Border.SetUShape(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < top or iOrientation > left)
            error("Border.SetUShape(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be top, right, bottom or left.");
        end
    end
//

    if (iOrientation == top)
        g:argBorderUShape:t = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == right)
        g:argBorderUShape:r = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == bottom)
        g:argBorderUShape:b = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == left)
        g:argBorderUShape:l = util:EnsureRotation(iIndex);
        return;
    end
end



nested function->null Border.SetUShapeFrom(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < top or iOrientation > left)
            error("Border.SetUShapeFrom(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be top, right, bottom or left.");
        end
    end
//

    if (iOrientation == top)
        g:argBorderUShape:t = util:EnsureRotation(iIndex);
        g:argBorderUShape:r = util:Rotate(g:argBorderUShape:t);
        g:argBorderUShape:b = util:Rotate(g:argBorderUShape:r);
        g:argBorderUShape:l = util:Rotate(g:argBorderUShape:b);
        return;
    end
    if (iOrientation == right)
        g:argBorderUShape:r = util:EnsureRotation(iIndex);
        g:argBorderUShape:b = util:Rotate(g:argBorderUShape:r);
        g:argBorderUShape:l = util:Rotate(g:argBorderUShape:b);
        g:argBorderUShape:t = util:Rotate(g:argBorderUShape:l);
        return;
    end
    if (iOrientation == bottom)
        g:argBorderUShape:b = util:EnsureRotation(iIndex);
        g:argBorderUShape:l = util:Rotate(g:argBorderUShape:b);
        g:argBorderUShape:t = util:Rotate(g:argBorderUShape:l);
        g:argBorderUShape:r = util:Rotate(g:argBorderUShape:t);
        return;
    end
    if (iOrientation == left)
        g:argBorderUShape:l = util:EnsureRotation(iIndex);
        g:argBorderUShape:t = util:Rotate(g:argBorderUShape:l);
        g:argBorderUShape:r = util:Rotate(g:argBorderUShape:t);
        g:argBorderUShape:b = util:Rotate(g:argBorderUShape:r);
        return;
    end
end



nested function->null Border.SetLShape(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < topLeft or iOrientation > bottomLeft)
            error("Border.SetLShape(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be topLeft, topRight, bottomRight or bottomLeft.");
        end
    end
//

    if (iOrientation == topLeft)
        g:argBorderLShape:tl = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == topRight)
        g:argBorderLShape:tr = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == bottomRight)
        g:argBorderLShape:br = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == bottomLeft)
        g:argBorderLShape:bl = util:EnsureRotation(iIndex);
        return;
    end
end



nested function->null Border.SetLShapeFrom(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < topLeft or iOrientation > bottomLeft)
            error("Border.SetLShapeFrom(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be topLeft, topRight, bottomRight or bottomLeft.");
        end
    end
//

    if (iOrientation == topLeft)
        g:argBorderLShape:tl = util:EnsureRotation(iIndex);
        g:argBorderLShape:tr = util:Rotate(g:argBorderLShape:tl);
        g:argBorderLShape:br = util:Rotate(g:argBorderLShape:tr);
        g:argBorderLShape:bl = util:Rotate(g:argBorderLShape:br);
        return;
    end
    if (iOrientation == topRight)
        g:argBorderLShape:tr = util:EnsureRotation(iIndex);
        g:argBorderLShape:br = util:Rotate(g:argBorderLShape:tr);
        g:argBorderLShape:bl = util:Rotate(g:argBorderLShape:br);
        g:argBorderLShape:tl = util:Rotate(g:argBorderLShape:bl);
        return;
    end
    if (iOrientation == bottomRight)
        g:argBorderLShape:br = util:EnsureRotation(iIndex);
        g:argBorderLShape:bl = util:Rotate(g:argBorderLShape:br);
        g:argBorderLShape:tl = util:Rotate(g:argBorderLShape:bl);
        g:argBorderLShape:tr = util:Rotate(g:argBorderLShape:tl);
        return;
    end
    if (iOrientation == bottomLeft)
        g:argBorderLShape:bl = util:EnsureRotation(iIndex);
        g:argBorderLShape:tl = util:Rotate(g:argBorderLShape:bl);
        g:argBorderLShape:tr = util:Rotate(g:argBorderLShape:tl);
        g:argBorderLShape:br = util:Rotate(g:argBorderLShape:tr);
        return;
    end
end



nested function->null Border.SetTShape(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < top or iOrientation > left)
            error("Border.SetTShape(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be top, right, bottom or left.");
        end
    end
//

    if (iOrientation == top)
        g:argBorderTShape:t = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == right)
        g:argBorderTShape:r = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == bottom)
        g:argBorderTShape:b = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == left)
        g:argBorderTShape:l = util:EnsureRotation(iIndex);
        return;
    end
end



nested function->null Border.SetTShapeFrom(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < top or iOrientation > left)
            error("Border.SetTShapeFrom(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be top, right, bottom or left.");
        end
    end
//

    if (iOrientation == top)
        g:argBorderTShape:t = util:EnsureRotation(iIndex);
        g:argBorderTShape:r = util:Rotate(g:argBorderTShape:t);
        g:argBorderTShape:b = util:Rotate(g:argBorderTShape:r);
        g:argBorderTShape:l = util:Rotate(g:argBorderTShape:b);
        return;
    end
    if (iOrientation == right)
        g:argBorderTShape:r = util:EnsureRotation(iIndex);
        g:argBorderTShape:b = util:Rotate(g:argBorderTShape:r);
        g:argBorderTShape:l = util:Rotate(g:argBorderTShape:b);
        g:argBorderTShape:t = util:Rotate(g:argBorderTShape:l);
        return;
    end
    if (iOrientation == bottom)
        g:argBorderTShape:b = util:EnsureRotation(iIndex);
        g:argBorderTShape:l = util:Rotate(g:argBorderTShape:b);
        g:argBorderTShape:t = util:Rotate(g:argBorderTShape:l);
        g:argBorderTShape:r = util:Rotate(g:argBorderTShape:t);
        return;
    end
    if (iOrientation == left)
        g:argBorderTShape:l = util:EnsureRotation(iIndex);
        g:argBorderTShape:t = util:Rotate(g:argBorderTShape:l);
        g:argBorderTShape:r = util:Rotate(g:argBorderTShape:t);
        g:argBorderTShape:b = util:Rotate(g:argBorderTShape:r);
        return;
    end
end



nested function->null Border.SetWallToIShape(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < top or iOrientation > left)
            error("Border.SetWallToIShape(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be top, right, bottom or left.");
        end
    end
//

    if (iOrientation == top)
        g:argBorderWallToIShape:t = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == right)
        g:argBorderWallToIShape:r = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == bottom)
        g:argBorderWallToIShape:b = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == left)
        g:argBorderWallToIShape:l = util:EnsureRotation(iIndex);
        return;
    end
end



nested function->null Border.SetWallToIShapeFrom(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < top or iOrientation > left)
            error("Border.SetWallToIShapeFrom(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be top, right, bottom or left.");
        end
    end
//

    if (iOrientation == top)
        g:argBorderWallToIShape:t = util:EnsureRotation(iIndex);
        g:argBorderWallToIShape:r = util:Rotate(g:argBorderWallToIShape:t);
        g:argBorderWallToIShape:b = util:Rotate(g:argBorderWallToIShape:r);
        g:argBorderWallToIShape:l = util:Rotate(g:argBorderWallToIShape:b);
        return;
    end
    if (iOrientation == right)
        g:argBorderWallToIShape:r = util:EnsureRotation(iIndex);
        g:argBorderWallToIShape:b = util:Rotate(g:argBorderWallToIShape:r);
        g:argBorderWallToIShape:l = util:Rotate(g:argBorderWallToIShape:b);
        g:argBorderWallToIShape:t = util:Rotate(g:argBorderWallToIShape:l);
        return;
    end
    if (iOrientation == bottom)
        g:argBorderWallToIShape:b = util:EnsureRotation(iIndex);
        g:argBorderWallToIShape:l = util:Rotate(g:argBorderWallToIShape:b);
        g:argBorderWallToIShape:t = util:Rotate(g:argBorderWallToIShape:l);
        g:argBorderWallToIShape:r = util:Rotate(g:argBorderWallToIShape:t);
        return;
    end
    if (iOrientation == left)
        g:argBorderWallToIShape:l = util:EnsureRotation(iIndex);
        g:argBorderWallToIShape:t = util:Rotate(g:argBorderWallToIShape:l);
        g:argBorderWallToIShape:r = util:Rotate(g:argBorderWallToIShape:t);
        g:argBorderWallToIShape:b = util:Rotate(g:argBorderWallToIShape:r);
        return;
    end
end



nested function->null Border.SetOuterToIShape(int iIndex, int iOrientation, int iIShapeOrientation)

//
    if (s:debug)
        if (iOrientation < topLeft or iOrientation > bottomLeft)
            error("Border.SetOuterToIShape(int " + iIndex.name() + ", int " + iOrientation.name() + ", int " + iIShapeOrientation.name() + ") -> " + iOrientation.name() + " needs to be topLeft, topRight, bottomRight or bottomLeft.");
        end
        if (iIShapeOrientation != vertical and iIShapeOrientation != horizontal)
            error("Border.SetOuterToIShape(int " + iIndex.name() + ", int " + iOrientation.name() + ", int " + iIShapeOrientation.name() + ") -> " + iIShapeOrientation.name() + " needs to be vertical or horizontal.");
        end
    end
//

    if (iIShapeOrientation == vertical)
        if (iOrientation == topLeft)
            g:argBorderOuterToIShape:tl:v = util:EnsureRotation(iIndex);
            return;
        end
        if (iOrientation == topRight)
            g:argBorderOuterToIShape:tr:v = util:EnsureRotation(iIndex);
            return;
        end
        if (iOrientation == bottomRight)
            g:argBorderOuterToIShape:br:v = util:EnsureRotation(iIndex);
            return;
        end
        if (iOrientation == bottomLeft)
            g:argBorderOuterToIShape:bl:v = util:EnsureRotation(iIndex);
            return;
        end
    end
    if (iIShapeOrientation == horizontal)
        if (iOrientation == topLeft)
            g:argBorderOuterToIShape:tl:h = util:EnsureRotation(iIndex);
            return;
        end
        if (iOrientation == topRight)
            g:argBorderOuterToIShape:tr:h = util:EnsureRotation(iIndex);
            return;
        end
        if (iOrientation == bottomRight)
            g:argBorderOuterToIShape:br:h = util:EnsureRotation(iIndex);
            return;
        end
        if (iOrientation == bottomLeft)
            g:argBorderOuterToIShape:bl:h = util:EnsureRotation(iIndex);
            return;
        end
    end
end



nested function->null Border.SetOuterToIShapeFrom(int iIndex, int iOrientation, int iIShapeOrientation)

//
    if (s:debug)
        if (iOrientation < topLeft or iOrientation > bottomLeft)
            error("Border.SetOuterToIShapeFrom(int " + iIndex.name() + ", int " + iOrientation.name() + ", int " + iIShapeOrientation.name() + ") -> " + iOrientation.name() + " needs to be topLeft, topRight, bottomRight or bottomLeft.");
        end
        if (iIShapeOrientation != vertical and iIShapeOrientation != horizontal)
            error("Border.SetOuterToIShapeFrom(int " + iIndex.name() + ", int " + iOrientation.name() + ", int " + iIShapeOrientation.name() + ") -> " + iIShapeOrientation.name() + " needs to be vertical or horizontal.");
        end
    end
//

    if (iIShapeOrientation == vertical)
        if (iOrientation == topLeft)
            g:argBorderOuterToIShape:tl:v = util:EnsureRotation(iIndex);
            g:argBorderOuterToIShape:tr:v = util:MirrorV(g:argBorderOuterToIShape:tl:v);
            g:argBorderOuterToIShape:br:v = util:MirrorH(g:argBorderOuterToIShape:tr:v);
            g:argBorderOuterToIShape:bl:v = util:MirrorV(g:argBorderOuterToIShape:br:v);
            g:argBorderOuterToIShape:tl:h = util:Rotate(g:argBorderOuterToIShape:bl:v);
            g:argBorderOuterToIShape:tr:h = util:MirrorV(g:argBorderOuterToIShape:tl:h);
            g:argBorderOuterToIShape:br:h = util:MirrorH(g:argBorderOuterToIShape:tr:h);
            g:argBorderOuterToIShape:bl:h = util:MirrorV(g:argBorderOuterToIShape:br:h);
            return;
        end
        if (iOrientation == topRight)
            g:argBorderOuterToIShape:tr:v = util:EnsureRotation(iIndex);
            g:argBorderOuterToIShape:br:v = util:MirrorH(g:argBorderOuterToIShape:tr:v);
            g:argBorderOuterToIShape:bl:v = util:MirrorV(g:argBorderOuterToIShape:br:v);
            g:argBorderOuterToIShape:tl:h = util:Rotate(g:argBorderOuterToIShape:bl:v);
            g:argBorderOuterToIShape:tr:h = util:MirrorV(g:argBorderOuterToIShape:tl:h);
            g:argBorderOuterToIShape:br:h = util:MirrorH(g:argBorderOuterToIShape:tr:h);
            g:argBorderOuterToIShape:bl:h = util:MirrorV(g:argBorderOuterToIShape:br:h);
            g:argBorderOuterToIShape:tl:v = util:Rotate(g:argBorderOuterToIShape:bl:h);
            return;
        end
        if (iOrientation == bottomRight)
            g:argBorderOuterToIShape:br:v = util:EnsureRotation(iIndex);
            g:argBorderOuterToIShape:bl:v = util:MirrorV(g:argBorderOuterToIShape:br:v);
            g:argBorderOuterToIShape:tl:h = util:Rotate(g:argBorderOuterToIShape:bl:v);
            g:argBorderOuterToIShape:tr:h = util:MirrorV(g:argBorderOuterToIShape:tl:h);
            g:argBorderOuterToIShape:br:h = util:MirrorH(g:argBorderOuterToIShape:tr:h);
            g:argBorderOuterToIShape:bl:h = util:MirrorV(g:argBorderOuterToIShape:br:h);
            g:argBorderOuterToIShape:tl:v = util:Rotate(g:argBorderOuterToIShape:bl:h);
            g:argBorderOuterToIShape:tr:v = util:MirrorV(g:argBorderOuterToIShape:tl:v);
            return;
        end
        if (iOrientation == bottomLeft)
            g:argBorderOuterToIShape:bl:v = util:EnsureRotation(iIndex);
            g:argBorderOuterToIShape:tl:h = util:Rotate(g:argBorderOuterToIShape:bl:v);
            g:argBorderOuterToIShape:tr:h = util:MirrorV(g:argBorderOuterToIShape:tl:h);
            g:argBorderOuterToIShape:br:h = util:MirrorH(g:argBorderOuterToIShape:tr:h);
            g:argBorderOuterToIShape:bl:h = util:MirrorV(g:argBorderOuterToIShape:br:h);
            g:argBorderOuterToIShape:tl:v = util:Rotate(g:argBorderOuterToIShape:bl:h);
            g:argBorderOuterToIShape:tr:v = util:MirrorV(g:argBorderOuterToIShape:tl:v);
            g:argBorderOuterToIShape:br:v = util:MirrorH(g:argBorderOuterToIShape:tr:v);
            return;
        end
    end
    if (iIShapeOrientation == horizontal)
        if (iOrientation == topLeft)
            g:argBorderOuterToIShape:tl:h = util:EnsureRotation(iIndex);
            g:argBorderOuterToIShape:tr:h = util:MirrorV(g:argBorderOuterToIShape:tl:h);
            g:argBorderOuterToIShape:br:h = util:MirrorH(g:argBorderOuterToIShape:tr:h);
            g:argBorderOuterToIShape:bl:h = util:MirrorV(g:argBorderOuterToIShape:br:h);
            g:argBorderOuterToIShape:tl:v = util:Rotate(g:argBorderOuterToIShape:bl:h);
            g:argBorderOuterToIShape:tr:v = util:MirrorV(g:argBorderOuterToIShape:tl:v);
            g:argBorderOuterToIShape:br:v = util:MirrorH(g:argBorderOuterToIShape:tr:v);
            g:argBorderOuterToIShape:bl:v = util:MirrorV(g:argBorderOuterToIShape:br:v);
            return;
        end
        if (iOrientation == topRight)
            g:argBorderOuterToIShape:tr:h = util:EnsureRotation(iIndex);
            g:argBorderOuterToIShape:br:h = util:MirrorH(g:argBorderOuterToIShape:tr:h);
            g:argBorderOuterToIShape:bl:h = util:MirrorV(g:argBorderOuterToIShape:br:h);
            g:argBorderOuterToIShape:tl:v = util:Rotate(g:argBorderOuterToIShape:bl:h);
            g:argBorderOuterToIShape:tr:v = util:MirrorV(g:argBorderOuterToIShape:tl:v);
            g:argBorderOuterToIShape:br:v = util:MirrorH(g:argBorderOuterToIShape:tr:v);
            g:argBorderOuterToIShape:bl:v = util:MirrorV(g:argBorderOuterToIShape:br:v);
            g:argBorderOuterToIShape:tl:h = util:Rotate(g:argBorderOuterToIShape:bl:v);
            return;
        end
        if (iOrientation == bottomRight)
            g:argBorderOuterToIShape:br:h = util:EnsureRotation(iIndex);
            g:argBorderOuterToIShape:bl:h = util:MirrorV(g:argBorderOuterToIShape:br:h);
            g:argBorderOuterToIShape:tl:v = util:Rotate(g:argBorderOuterToIShape:bl:h);
            g:argBorderOuterToIShape:tr:v = util:MirrorV(g:argBorderOuterToIShape:tl:v);
            g:argBorderOuterToIShape:br:v = util:MirrorH(g:argBorderOuterToIShape:tr:v);
            g:argBorderOuterToIShape:bl:v = util:MirrorV(g:argBorderOuterToIShape:br:v);
            g:argBorderOuterToIShape:tl:h = util:Rotate(g:argBorderOuterToIShape:bl:v);
            g:argBorderOuterToIShape:tr:h = util:MirrorV(g:argBorderOuterToIShape:tl:h);
            return;
        end
        if (iOrientation == bottomLeft)
            g:argBorderOuterToIShape:bl:h = util:EnsureRotation(iIndex);
            g:argBorderOuterToIShape:tl:v = util:Rotate(g:argBorderOuterToIShape:bl:h);
            g:argBorderOuterToIShape:tr:v = util:MirrorV(g:argBorderOuterToIShape:tl:v);
            g:argBorderOuterToIShape:br:v = util:MirrorH(g:argBorderOuterToIShape:tr:v);
            g:argBorderOuterToIShape:bl:v = util:MirrorV(g:argBorderOuterToIShape:br:v);
            g:argBorderOuterToIShape:tl:h = util:Rotate(g:argBorderOuterToIShape:bl:v);
            g:argBorderOuterToIShape:tr:h = util:MirrorV(g:argBorderOuterToIShape:tl:h);
            g:argBorderOuterToIShape:br:h = util:MirrorH(g:argBorderOuterToIShape:tr:h);
            return;
        end
    end
end



nested function->null Border.SetOuterToDoubleIShape(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < topLeft or iOrientation > bottomLeft)
            error("Border.SetOuterToDoubleIShape(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be topLeft, topRight, bottomRight or bottomLeft.");
        end
    end
//

    if (iOrientation == topLeft)
        g:argBorderOuterToDoubleIShape:tl = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == topRight)
        g:argBorderOuterToDoubleIShape:tr = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == bottomRight)
        g:argBorderOuterToDoubleIShape:br = util:EnsureRotation(iIndex);
        return;
    end
    if (iOrientation == bottomLeft)
        g:argBorderOuterToDoubleIShape:bl = util:EnsureRotation(iIndex);
        return;
    end
end



nested function->null Border.SetOuterToDoubleIShapeFrom(int iIndex, int iOrientation)

//
    if (s:debug)
        if (iOrientation < topLeft or iOrientation > bottomLeft)
            error("Border.SetOuterToDoubleIShapeFrom(int " + iIndex.name() + ", int " + iOrientation.name() + ") -> " + iOrientation.name() + " needs to be topLeft, topRight, bottomRight or bottomLeft.");
        end
    end
//

    if (iOrientation == topLeft)
        g:argBorderOuterToDoubleIShape:tl = util:EnsureRotation(iIndex);
        g:argBorderOuterToDoubleIShape:tr = util:Rotate(g:argBorderOuterToDoubleIShape:tl);
        g:argBorderOuterToDoubleIShape:br = util:Rotate(g:argBorderOuterToDoubleIShape:tr);
        g:argBorderOuterToDoubleIShape:bl = util:Rotate(g:argBorderOuterToDoubleIShape:br);
        return;
    end
    if (iOrientation == topRight)
        g:argBorderOuterToDoubleIShape:tr = util:EnsureRotation(iIndex);
        g:argBorderOuterToDoubleIShape:br = util:Rotate(g:argBorderOuterToDoubleIShape:tr);
        g:argBorderOuterToDoubleIShape:bl = util:Rotate(g:argBorderOuterToDoubleIShape:br);
        g:argBorderOuterToDoubleIShape:tl = util:Rotate(g:argBorderOuterToDoubleIShape:bl);
        return;
    end
    if (iOrientation == bottomRight)
        g:argBorderOuterToDoubleIShape:br = util:EnsureRotation(iIndex);
        g:argBorderOuterToDoubleIShape:bl = util:Rotate(g:argBorderOuterToDoubleIShape:br);
        g:argBorderOuterToDoubleIShape:tl = util:Rotate(g:argBorderOuterToDoubleIShape:bl);
        g:argBorderOuterToDoubleIShape:tr = util:Rotate(g:argBorderOuterToDoubleIShape:tl);
        return;
    end
    if (iOrientation == bottomLeft)
        g:argBorderOuterToDoubleIShape:bl = util:EnsureRotation(iIndex);
        g:argBorderOuterToDoubleIShape:tl = util:Rotate(g:argBorderOuterToDoubleIShape:bl);
        g:argBorderOuterToDoubleIShape:tr = util:Rotate(g:argBorderOuterToDoubleIShape:tl);
        g:argBorderOuterToDoubleIShape:br = util:Rotate(g:argBorderOuterToDoubleIShape:tr);
        return;
    end
end



nested function->null Border.SetCross(int iIndex)

    g:argBorderCross = util:EnsureRotation(iIndex);
end



nested function->null Border.SetDot(int iIndex)

    g:argBorderDot = util:EnsureRotation(iIndex);
end



nested function->null Border.SetFill(int iIndex)

    g:argBorderFill = iIndex;
end



nested function->null Border.SetTestIndices(array int aIndices)

    g:argBorderTestIndices = aIndices;
end





///////////////////////////////////////
//
/******************************************************************************

*/
function->null internal:ResetFillObjectsArgs()

    array object aEmpty;
    g:insertedObjects = aEmpty;
end





///////////////////////////////////////
//
/******************************************************************************

*/
function->null Run()
    nested(
        Filter, Shift, Checkerboard, 
        Border, FillObjects
    )

    invoke(nested);
end



nested function->null Run.Filter()

    NewRun();
    OverrideLayer();

    Insert(0).If(
        IndexAt(0).IsNot(g:argFilterIndices)
    );

    NewRun();
    internal:ResetFilterArgs();
end



nested function->null Run.Shift()

    NewRun();

    coord cOffset = g:argShiftOffset;

    for (i = 0 to g:argShiftIndices.last)
        Insert(0).If(
            IndexAt(0).Is(g:argShiftIndices[i])
        );
    end
    for (i = 0 to g:argShiftIndices.last)
        Insert(g:argShiftIndices[i]).If(
            IndexAt(cOffset).Is(g:argShiftIndices[i])
        ).NoDefaultPosRule();
    end

    NewRun();
    internal:ResetShiftArgs();
end



nested function->null Run.Checkerboard()

    NewRun();
    OverrideLayer();

    int iIndex1 = g:argCheckerboardIndex1;
    int iIndex2 = g:argCheckerboardIndex2;
    int iMask = g:mask.N;

    if (util:SameRotation(iMask, iIndex1))
        iMask = iMask.V;
    end
    if (util:SameRotation(iMask, iIndex2))
        iMask = iMask.VH;
    end

    coord cSize = g:argCheckerboardSize;

    Insert(iIndex2);
    Insert(iMask).If(
        IndexAt(0).IsEmpty(), IndexAt([util:Negate(cSize.x), 0], [0, util:Negate(cSize.y)]).IsNot(iMask, iIndex1)
    );
    Insert(iIndex1).If(
        IndexAt(0).Is(iIndex2), IndexAt([util:Negate(cSize.x), 0], [0, util:Negate(cSize.y)]).IsNot(iMask, iIndex1)
    );

    NewRun();
    OverrideLayer();

    Replace(iMask, 0);

    NewRun();
    internal:ResetCheckerboardArgs();
end



nested function->null Run.Border()

    NewRun();

    if (g:argBorderWall:t != -1)
        Insert(g:argBorderWall:t).If(
            IndexAt(0).IsWall(top).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
        Insert(g:argBorderWall:t).If(
            IndexAt(0).IsOuterCorner(topLeft).IsEdge(left).TestIndices(g:argBorderTestIndices)
        );
        Insert(g:argBorderWall:t).If(
            IndexAt(0).IsOuterCorner(topRight).IsEdge(right).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderWall:r != -1)
        Insert(g:argBorderWall:r).If(
            IndexAt(0).IsWall(right).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
        Insert(g:argBorderWall:r).If(
            IndexAt(0).IsOuterCorner(topRight).IsEdge(top).TestIndices(g:argBorderTestIndices)
        );
        Insert(g:argBorderWall:r).If(
            IndexAt(0).IsOuterCorner(bottomRight).IsEdge(bottom).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderWall:b != -1)
        Insert(g:argBorderWall:b).If(
            IndexAt(0).IsWall(bottom).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
        Insert(g:argBorderWall:b).If(
            IndexAt(0).IsOuterCorner(bottomLeft).IsEdge(left).TestIndices(g:argBorderTestIndices)
        );
        Insert(g:argBorderWall:b).If(
            IndexAt(0).IsOuterCorner(bottomRight).IsEdge(right).TestIndices(g:argBorderTestIndices)
        );    
    end
    if (g:argBorderWall:l != -1)
        Insert(g:argBorderWall:l).If(
            IndexAt(0).IsWall(left).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
        Insert(g:argBorderWall:l).If(
            IndexAt(0).IsOuterCorner(topLeft).IsEdge(top).TestIndices(g:argBorderTestIndices)
        );
        Insert(g:argBorderWall:l).If(
            IndexAt(0).IsOuterCorner(bottomLeft).IsEdge(bottom).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuter:tl != -1)
        Insert(g:argBorderOuter:tl).If(
            IndexAt(0).IsOuterCorner(topLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuter:tr != -1)
        Insert(g:argBorderOuter:tr).If(
            IndexAt(0).IsOuterCorner(topRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuter:br != -1)
        Insert(g:argBorderOuter:br).If(
            IndexAt(0).IsOuterCorner(bottomRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuter:bl != -1)
        Insert(g:argBorderOuter:bl).If(
            IndexAt(0).IsOuterCorner(bottomLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderInner:tl != -1)
        Insert(g:argBorderInner:tl).If(
            IndexAt(0).IsInnerCorner(topLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderInner:tr != -1)
        Insert(g:argBorderInner:tr).If(
            IndexAt(0).IsInnerCorner(topRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderInner:br != -1)
        Insert(g:argBorderInner:br).If(
            IndexAt(0).IsInnerCorner(bottomRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderInner:bl != -1)
        Insert(g:argBorderInner:bl).If(
            IndexAt(0).IsInnerCorner(bottomLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderDiagonal:tl != -1)
        Insert(g:argBorderDiagonal:tl).If(
            IndexAt(0).IsInnerCorner(topLeft, bottomRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderDiagonal:tr != -1)
        Insert(g:argBorderDiagonal:tr).If(
            IndexAt(0).IsInnerCorner(topRight, bottomLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderIShape:v != -1)
        Insert(g:argBorderIShape:v).If(
            IndexAt(0).IsWall(left, right).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
        Insert(g:argBorderIShape:v).If(
            IndexAt(0).IsOuterCorner(topLeft, topRight).IsEdge(top).TestIndices(g:argBorderTestIndices)
        );
        Insert(g:argBorderIShape:v).If(
            IndexAt(0).IsOuterCorner(bottomLeft, bottomRight).IsEdge(bottom).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderIShape:h != -1)
        Insert(g:argBorderIShape:h).If(
            IndexAt(0).IsWall(top, bottom).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
        Insert(g:argBorderIShape:h).If(
            IndexAt(0).IsOuterCorner(topLeft, bottomLeft).IsEdge(left).TestIndices(g:argBorderTestIndices)
        );
        Insert(g:argBorderIShape:h).If(
            IndexAt(0).IsOuterCorner(topRight, bottomRight).IsEdge(right).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderUShape:t != -1)
        Insert(g:argBorderUShape:t).If(
            IndexAt(0).IsOuterCorner(topLeft, topRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderUShape:r != -1)
        Insert(g:argBorderUShape:r).If(
            IndexAt(0).IsOuterCorner(topRight, bottomRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderUShape:b != -1)
        Insert(g:argBorderUShape:b).If(
            IndexAt(0).IsOuterCorner(bottomRight, bottomLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderUShape:l != -1)
        Insert(g:argBorderUShape:l).If(
            IndexAt(0).IsOuterCorner(bottomLeft, topLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderLShape:tl != -1)
        Insert(g:argBorderLShape:tl).If(
            IndexAt(0).IsOuterCorner(topLeft).IsInnerCorner(bottomRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderLShape:tr != -1)
        Insert(g:argBorderLShape:tr).If(
            IndexAt(0).IsOuterCorner(topRight).IsInnerCorner(bottomLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderLShape:br != -1)
        Insert(g:argBorderLShape:br).If(
            IndexAt(0).IsOuterCorner(bottomRight).IsInnerCorner(topLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderLShape:bl != -1)
        Insert(g:argBorderLShape:bl).If(
            IndexAt(0).IsOuterCorner(bottomLeft).IsInnerCorner(topRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderTShape:t != -1)
        Insert(g:argBorderTShape:t).If(
            IndexAt(0).IsWall(top).IsInnerCorner(bottomRight, bottomLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderTShape:r != -1)
        Insert(g:argBorderTShape:r).If(
            IndexAt(0).IsWall(right).IsInnerCorner(bottomLeft, topLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderTShape:b != -1)
        Insert(g:argBorderTShape:b).If(
            IndexAt(0).IsWall(bottom).IsInnerCorner(topLeft, topRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderTShape:l != -1)
        Insert(g:argBorderTShape:l).If(
            IndexAt(0).IsWall(left).IsInnerCorner(topRight, bottomRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderWallToIShape:t != -1)
        Insert(g:argBorderWallToIShape:t).If(
            IndexAt(0).IsInnerCorner(topLeft, topRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderWallToIShape:r != -1)
        Insert(g:argBorderWallToIShape:r).If(
            IndexAt(0).IsInnerCorner(topRight, bottomRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderWallToIShape:b != -1)
        Insert(g:argBorderWallToIShape:b).If(
            IndexAt(0).IsInnerCorner(bottomRight, bottomLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderWallToIShape:l != -1)
        Insert(g:argBorderWallToIShape:l).If(
            IndexAt(0).IsInnerCorner(bottomLeft, topLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuterToIShape:tl:v != -1)
        Insert(g:argBorderOuterToIShape:tl:v).If(
            IndexAt(0).IsWall(left).IsInnerCorner(topRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuterToIShape:tr:v != -1)
        Insert(g:argBorderOuterToIShape:tr:v).If(
            IndexAt(0).IsWall(right).IsInnerCorner(topLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuterToIShape:br:v != -1)
        Insert(g:argBorderOuterToIShape:br:v).If(
            IndexAt(0).IsWall(right).IsInnerCorner(bottomLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuterToIShape:bl:v != -1)
        Insert(g:argBorderOuterToIShape:bl:v).If(
            IndexAt(0).IsWall(left).IsInnerCorner(bottomRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuterToIShape:tl:h != -1)
        Insert(g:argBorderOuterToIShape:tl:h).If(
            IndexAt(0).IsWall(top).IsInnerCorner(bottomLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuterToIShape:tr:h != -1)
        Insert(g:argBorderOuterToIShape:tr:h).If(
            IndexAt(0).IsWall(top).IsInnerCorner(bottomRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuterToIShape:br:h != -1)
        Insert(g:argBorderOuterToIShape:br:h).If(
            IndexAt(0).IsWall(bottom).IsInnerCorner(topRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuterToIShape:bl:h != -1)
        Insert(g:argBorderOuterToIShape:bl:h).If(
            IndexAt(0).IsWall(bottom).IsInnerCorner(topLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end   
    if (g:argBorderOuterToDoubleIShape:tl != -1)
        Insert(g:argBorderOuterToDoubleIShape:tl).If(
            IndexAt(0).IsInnerCorner(bottomLeft, topLeft, topRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuterToDoubleIShape:tr != -1)
        Insert(g:argBorderOuterToDoubleIShape:tr).If(
            IndexAt(0).IsInnerCorner(topLeft, topRight, bottomRight).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuterToDoubleIShape:br != -1)
        Insert(g:argBorderOuterToDoubleIShape:br).If(
            IndexAt(0).IsInnerCorner(topRight, bottomRight, bottomLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderOuterToDoubleIShape:bl != -1)
        Insert(g:argBorderOuterToDoubleIShape:bl).If(
            IndexAt(0).IsInnerCorner(bottomRight, bottomLeft, topLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderCross != -1)
        Insert(g:argBorderCross).If(
            IndexAt(0).IsInnerCorner(topLeft, topRight, bottomRight, bottomLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end
    if (g:argBorderDot != -1)
        Insert(g:argBorderDot).If(
            IndexAt(0).IsOuterCorner(topLeft, topRight, bottomRight, bottomLeft).IsNotEdge(all).TestIndices(g:argBorderTestIndices)
        );
    end

    NewRun();
    internal:ResetBorderArgs();
end



nested function->null Run.FillObjects()

//
    if (s:debug)
        if (g:insertedObjects.count == 0)
            warning("Run.FillObjects() -> No objects were inserted, function had no effect.");
            return;
        end
    end
//

    NewRun();

    for (i = 0 to g:insertedObjects.last)
        coord cAnchor = g:insertedObjects[i].anchor;

        for (j = 0 to g:insertedObjects[i].last)
            coord cRelativePos = util:RelativePos(cAnchor, g:insertedObjects[i][j]);

            Insert(g:insertedObjects[i][j]).If(
                IndexAt([cRelativePos.x * -1, cRelativePos.y * -1]).Is(cAnchor)
            ).NoDefaultPosRule();
        end
    end

    NewRun();
    internal:ResetFillObjectsArgs();
end
