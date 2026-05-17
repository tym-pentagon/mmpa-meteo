/**
Program pro výpočet pozic vrcholů pentagonu a čtyřúhelníků v menu. Exportuje kód v C a vypíše jej do konzole. 

Spuštěno na Khan Academy. 
*/

var shapeName = "pentagon"; 
var nodes = 5; 
var amplitude = 60; 
var offset = 3; 
var amplitude2 = 95;
var mainShapeGeneratedCode = "Point " + shapeName + "[" + String(nodes) + "] = {";
var quadsGeneratedCode = "Point ctyruhelniky[][" + String(nodes) + "] = {";

background(255, 255, 255);
fill(0, 0, 0);
noStroke();
rect(width/2 - 320/2, height/2 - 480/2, 320, 480);

strokeWeight(1);

function getCoordinates(angle, amplitude) {
    var x = cos(angle - 90) * amplitude;
    var y = sin(angle - 90) * amplitude;
    return { x:x, y:y };
}

function calculateOffsetPoint(angle, amplitude, offset, direction) {
    /**
        angle - angle of the shape's node relative to origin
        amplitude - distance from the shape's node to the origin
        offset - the radius of the circle that the offset points are located on
        direction - "left" or "right"
    */
    
    var circleCenterX = cos(angle - 90) * (amplitude + offset);
    var circleCenterY = sin(angle - 90) * (amplitude + offset);
    
    stroke(255, 0, 0);
    //ellipse(circleCenterX, circleCenterY, offset * 2, offset * 2); 
    
    var angleOffset = 0;
    
    if (direction === "left") {
        angleOffset = -60; 
    }
    else if (direction === "right") {
        angleOffset = 60;
    }
    else {
        throw { message:'Invalid direction (must be either "left" or "right")' };
    }
    
    var offsetPointX = circleCenterX + cos(angle - 90 + angleOffset) * offset;
    var offsetPointY = circleCenterY + sin(angle - 90 + angleOffset) * offset;
    
    return { x:offsetPointX, y:offsetPointY }; 
}

function prepareCoordinateForExport(coordinate, type) {
    /** Prepares a coordinate for export.
        type - "x" or "y"
    */
    
    var origin = 0; 
    if (type === "x") {
        origin = 320/2;
    }
    else if (type === "y") {
        origin = 480/2;
    }
    else {
        throw { message:'Invalid coordinate type (must be either "x" or "y")' };
    }
    
    return String(round(origin + coordinate)); 
}

function movePoint(x, y, angle, distance) {
    /** Moves a point from its starting coordinates by a specified angle and distance. */
    var pointX = x + cos(angle - 90) * distance;
    var pointY = y + sin(angle - 90) * distance;
    
    return { x:pointX, y:pointY };
}

pushMatrix();
    translate(width/2, height/2);
    
    for (var i = 0; i < nodes; i ++) {
        var currentNode = getCoordinates(i * 360 / nodes, amplitude);
        var nextNode = getCoordinates((i + 1) * 360 / nodes, amplitude);
        
        stroke(18, 255, 3);
        line(currentNode.x, currentNode.y, nextNode.x, nextNode.y);
        
        mainShapeGeneratedCode += "\n\t{" + prepareCoordinateForExport(currentNode.x, "x") + ", " + prepareCoordinateForExport(currentNode.y, "y") + "}" + ((i !== nodes - 1) ? ", " : ""); 
        
        var currentNodeOffsetPoint = calculateOffsetPoint(i * 360 / nodes, amplitude, offset, "right"); 
        var nextNodeOffsetPoint = calculateOffsetPoint((i + 1) * 360 / nodes, amplitude, offset, "left"); 
        
        var currentNodeOuterOffsetPoint = movePoint(currentNodeOffsetPoint.x, currentNodeOffsetPoint.y, (i * 360 / nodes), amplitude2); 
        var nextNodeOuterOffsetPoint = movePoint(nextNodeOffsetPoint.x, nextNodeOffsetPoint.y, ((i + 1) * 360 / nodes), amplitude2); 
        
        stroke(18, 255, 3);
        quad(currentNodeOffsetPoint.x, currentNodeOffsetPoint.y, nextNodeOffsetPoint.x, nextNodeOffsetPoint.y, nextNodeOuterOffsetPoint.x, nextNodeOuterOffsetPoint.y, currentNodeOuterOffsetPoint.x, currentNodeOuterOffsetPoint.y);
        
        quadsGeneratedCode += "\n\t{ {" + prepareCoordinateForExport(currentNodeOffsetPoint.x, "x") + ", " + prepareCoordinateForExport(currentNodeOffsetPoint.y, "y") + "}, {" + prepareCoordinateForExport(nextNodeOffsetPoint.x, "x") + ", " + prepareCoordinateForExport(nextNodeOffsetPoint.y, "y") + "}, {" + prepareCoordinateForExport(nextNodeOuterOffsetPoint.x, "x") + ", " + prepareCoordinateForExport(nextNodeOuterOffsetPoint.y, "y") + "}, {" + prepareCoordinateForExport(currentNodeOuterOffsetPoint.x, "x") + ", " + prepareCoordinateForExport(currentNodeOuterOffsetPoint.y, "y") + "} }" + ((i !== nodes - 1) ? ", " : "");
    }
popMatrix();


mainShapeGeneratedCode += "\n};"; 
println(mainShapeGeneratedCode); 

println("\n\n"); 

quadsGeneratedCode += "\n};";
println(quadsGeneratedCode); 