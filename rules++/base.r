
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



function->array int util:RemoveRotation(array float aIndices)

    array int aResult;
    if (aIndices.count != 0)
        for (i = 0 to aIndices.last)
            aResult.push(aIndices[i]);
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



function->array coord util:PosRange(range rX, range rY)

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



function->array coord util:PosRange(range rX, int iY)

    array int aX = util:ArrayInt(rX);

    array coord aResult;
    for (i = 0 to aX.last)
        aResult.push([aX[i], iY]);
    end
    return aResult;
end



function->array coord util:PosRange(int iX, range rY)

    array int aY = util:ArrayInt(rY);

    array coord aResult;
    for (i = 0 to aY.last)
        aResult.push([iX, aY[i]]);
    end
    return aResult;
end



function->array float util:Copies(float fValue, int iCopies)

//
    if (s:debug)
        if (iCopies < 1)
            error("util:Copies(float fValue, int iCopies) -> iCopies needs to be greater than 0.");
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



function->float util:SumOf(array float aValues)

//
    if (s:debug)
        if (aValues.count == 0)
            error("util:SumOf(array float aValues) -> aValues cannot be empty.");
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
            error("util:Normalize(array float aValues, float fBound) -> aValues cannot be empty.");
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
            error("Unbias(array float aProbabilities) -> aProbabilities cannot be empty.");
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
        float fUnbiased = 100.0 / (aClamped[i] / fRemaining * 100.0);
        fRemaining = fRemaining - aClamped[i];
        aResult.push(fUnbiased);
    end
    return aResult;
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
            error("NewRun(int iCopies) -> iCopies needs to be greater than 0.");
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

//
    if (s:debug)
        if (cTopLeft.x > cBottomRight.x or cTopLeft.y > cBottomRight.y)
            warning("Rect(int iTopLeft, int iBottomRight) -> iTopLeft is not a top left corner of the rectangle.");
        end
    end
//

    array int aResult;
    for (x = cTopLeft.x to cBottomRight.x)
        for (y = cTopLeft.y to cBottomRight.y)
            aResult.push([x, y]);
        end
    end
    return Indices(aResult);
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

    if (g:roll == false)
        if (g:randomize)
            for (i = 0 to iLast)
                aProbabilities.push(g:argInsertChance[g:argInsertChanceIndex]);

                g:argInsertChanceIndex = g:argInsertChanceIndex + 1;
                if (g:argInsertChanceIndex > g:argInsertChance.last)
                    g:argInsertChanceIndex = 0;
                end
            end

            g:argInsertChance = util:Unbias(aProbabilities);
        end
        if (g:randomize == false)
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
        NoDefaultPosRule, Chance, Roll, If,
        TestIndices
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

        if (g:vTestIndices.has(0))
            insert.rule.pos = [0, 0];
            insert.rule.pos.type = empty;
        end
        util:Chance(g:argInsertChance[g:argInsertChanceIndex]);

        invoke(nested);

        g:argInsertChanceIndex = g:argInsertChanceIndex + 1;
    end

    if (true)
        array int aEmpty;
        g:vTestIndices = aEmpty;
    end
    if (true)
        array float aEmpty;
        g:argInsertChance = aEmpty;
    end
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
            warning("Insert.At(coord cPos) -> cPos.x was negative, function had no effect.");
            return;
        end
        if (cPos.y < 0)
            warning("Insert.At(coord cPos) -> cPos.y was negative, function had no effect.");
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
            warning("Insert.Chance(array float aProbabilities) -> aProbabilities was empty, function had no effect.");
            return;
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



nested function->null Insert.TestIndices(array int aIndices)

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("Insert.TestIndices(array int aIndices) -> aIndices was empty, function had no effect.");
            return;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < 0 or aIndices[i] > 255)
                error("Insert.TestIndices(array int aIndices) -> values need to be in range [0-255].");
            end
        end
    end
//

    if (g:initInsert)
        g:vTestIndices = aIndices;
        return;
    end
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

int top         = 100;
int right       = 101;
int bottom      = 102;
int left        = 103;
int topLeft     = 104;
int topRight    = 105;
int bottomLeft  = 106;
int bottomRight = 107;
int this        = 99999;
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
        Is, IsNot, IsEmpty, IsEmptyAt, IsFull, IsFullAt, IsOut, IsNotOut,
        IsEdge, IsNotEdge,
        IsNextTo, IsNotNextTo,
        IsWall, IsOuterCorner, IsInnerCorner,
        HasSpaceFor,
        IsOverlapping, IsNotOverlapping
    )

//
    if (s:debug)
        if (aCoords.count == 0)
            warning("IndexAt(array coord aCoords) -> aCoords was empty, function had no effect.");
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

    internal:IndexAtResetFlags();
    internal:ResetFlags();
    return true;
end



nested function->bool IndexAt.Is(array int aIndices)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("IndexAt.Is(array int aIndices) -> aIndices was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if ((aIndices[i] < -1 or aIndices[i] > 255) and aIndices[i] != this)
                error("IndexAt.Is(array int aIndices) -> values need to be in range [-1-255].");
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
            warning("IndexAt.IsNot(array int aIndices) -> aIndices was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if ((aIndices[i] < -1 or aIndices[i] > 255) and aIndices[i] != this)
                error("IndexAt.IsNot(array int aIndices) -> values need to be in range [-1-255].");
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
            warning("IndexAt.IsEmptyAt(array int aOrientations) -> aOrientations was empty, function had no effect.");
            return false;
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
        if (iOrientation == bottomLeft)
            insert.rule.pos = [iX - 1, iY + 1];
            insert.rule.pos.type = empty;
        end
        if (iOrientation == bottomRight)
            insert.rule.pos = [iX + 1, iY + 1];
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
            warning("IndexAt.IsFullAt(array int aOrientations) -> aOrientations was empty, function had no effect.");
            return false;
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
        if (iOrientation == bottomLeft)
            insert.rule.pos = [iX - 1, iY + 1];
            insert.rule.pos.type = full;
        end
        if (iOrientation == bottomRight)
            insert.rule.pos = [iX + 1, iY + 1];
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



nested function->bool IndexAt.IsEdge(int iOrientation)

    if (g:initIndexAt)
        return false;
    end

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
    return true;
end



nested function->bool IndexAt.IsNotEdge(array int aOrientations)

    if (g:initIndexAt)
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
    return true;
end



nested function->bool IndexAt.IsNextTo(array int aIndices)

    if (g:initIndexAt)
        return false;
    end

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("IndexAt.IsNextTo(array int aIndices) -> aIndices was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if ((aIndices[i] < -1 or aIndices[i] > 255) and aIndices[i] != this)
                error("IndexAt.IsNextTo(array int aIndices) -> values need to be in range [-1-255].");
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
            warning("IndexAt.IsNotNextTo(array int aIndices) -> aIndices was empty, function had no effect.");
            return false;
        end

        for (i = 0 to aIndices.last)
            if ((aIndices[i] < -1 or aIndices[i] > 255) and aIndices[i] != this)
                error("IndexAt.IsNotNextTo(array int aIndices) -> values need to be in range [-1-255].");
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
            warning("IndexAt.IsWall(array int aOrientations) -> aOrientations was empty, function had no effect.");
            return false;
        end
    end
//

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
            warning("IndexAt.IsOuterCorner(array int aOrientations) -> aOrientations was empty, function had no effect.");
            return false;
        end
    end
//

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
    return true;
end



nested function->bool IndexAt.IsInnerCorner(array int aOrientations)

    if (g:initIndexAt)
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
    return true;
end



nested function->bool IndexAt.HasSpaceFor(object oObject)

    if (g:initIndexAt)
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
            warning("IndexAt.IsOverlapping(array object aObjects) -> aObjects was empty, function had no effect.");
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
            warning("IndexAt.IsNotOverlapping(array object aObjects) -> aObjects was empty, function had no effect.");
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
/******************************************************************************

*/
function->null InsertObject(array object aObjects)
    nested(
        At,
        NoDefaultPosRule, Chance, Roll, If,
        TestIndices
    )

//
    if (s:debug)
        if (aObjects.count == 0)
            warning("InsertObject(array object aObjects) -> aObjects was empty, function had no effect.");
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

        insert.newrule;
        util:InsertIndex(g:vInsertIndex);

        if (g:vTestIndices.has(0))
            insert.rule.pos = [0, 0];
            insert.rule.pos.type = empty;
        end
        util:Chance(g:argInsertChance[g:argInsertChanceIndex]);

        invoke(nested);

        g:argInsertChanceIndex = g:argInsertChanceIndex + 1;
    end

    if (true)
        array int aEmpty;
        g:vTestIndices = aEmpty;
    end
    if (true)
        array float aEmpty;
        g:argInsertChance = aEmpty;
    end
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
            warning("InsertObject.At(coord cPos) -> cPos.x was negative, function had no effect.");
            return;
        end
        if (cPos.y < 0)
            warning("InsertObject.At(coord cPos) -> cPos.y was negative, function had no effect.");
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
            warning("InsertObject.Chance(array float aProbabilities) -> aProbabilities was empty, function had no effect.");
            return;
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



nested function->null InsertObject.TestIndices(array int aIndices)

//
    if (s:debug)
        if (aIndices.count == 0)
            warning("InsertObject.TestIndices(array int aIndices) -> aIndices was empty, function had no effect.");
            return;
        end

        for (i = 0 to aIndices.last)
            if (aIndices[i] < 0 or aIndices[i] > 255)
                error("InsertObject.TestIndices(array int aIndices) -> values need to be in range [0-255].");
            end
        end
    end
//

    if (g:initInsert)
        g:vTestIndices = aIndices;
        return;
    end
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
        HasSpace, Fits, IsOver,
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

    internal:ObjectResetFlags();
    internal:ResetFlags();
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

        if (aRelativePos.has(cTop) == false)
            insert.rule.pos = cTop;
            internal:TestIndicesEmpty();
        end
        if (aRelativePos.has(cRight) == false)
            insert.rule.pos = cRight;
            internal:TestIndicesEmpty();
        end
        if (aRelativePos.has(cBottom) == false)
            insert.rule.pos = cBottom;
            internal:TestIndicesEmpty();
        end
        if (aRelativePos.has(cLeft) == false)
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
            warning("Object.IsOver(array object aObjects) -> aObjects was empty, function had no effect.");
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



nested function->bool Object.IsEdge(int iOrientation)

    if (g:initObject)
        return false;
    end

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
    if (iOrientation == bottomLeft)
        insert.rule.pos = [0, g:vObjectBottom + 1];
        insert.rule.pos.type = index;
        insert.rule.pos.index = -1;

        insert.rule.pos = [g:vObjectLeft - 1, 0];
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
    return true;
end



nested function->bool Object.IsNotEdge(array int aOrientations)

    if (g:initObject)
        return false;
    end

//
    if (s:debug)
        if (aOrientations.count == 0)
            warning("Object.IsNotEdge(array int aOrientations) -> aOrientations was empty, function had no effect.");
            return false;
        end
    end
//

    for (i = 0 to aOrientations.last)
        if (aOrientations[i] == top)
            insert.rule.pos = [0, g:vObjectTop - 1];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (aOrientations[i] == right)
            insert.rule.pos = [g:vObjectRight + 1, 0];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (aOrientations[i] == bottom)
            insert.rule.pos = [0, g:vObjectBottom + 1];
            insert.rule.pos.type = notindex;
            insert.rule.pos.index = -1;
        end
        if (aOrientations[i] == left)
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
            warning("Object.IsNextTo(array object aObjects) -> aObjects was empty, function had no effect.");
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
                    if (aPos.has(cPos) == false)
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
            warning("Object.IsNotNextTo(array object aObjects) -> aObjects was empty, function had no effect.");
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
                if (aPos.has(cPos) == false)
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
            warning("Object.IsOverlapping(array object aObjects) -> aObjects was empty, function had no effect.");
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
                if (aPos.has(cPos) == false)
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
            warning("Object.IsNotOverlapping(array object aObjects) -> aObjects was empty, function had no effect.");
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
                if (aPos.has(cPos) == false)
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
