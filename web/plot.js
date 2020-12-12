// global vars
local_ip = '192.168.31.80';
global_ip = '85.143.113.155';
ip = local_ip;

var sessionID = 0;
var nVertex = 0;
var nArcs = 0;
var nodes = new vis.DataSet();
var edges = new vis.DataSet();
var container;
//-------------------------------------------------------

// UI functions
jQuery(function(){
    container = document.getElementById("mynetwork");

    jQuery('#nVertex').val(10);

    jQuery('#makeGraph').click(function(){
        makeGraph();
    });

    jQuery('#addArc').click(function(){
        addArc();
    });

    jQuery('#removeArc').click(function(){
        removeArc();
    });

    jQuery('#findPath').click(function(){
        findPath();
    });

    $(window).unload(function() { 
        endSession();
    });

});

// process functions
// SESSION HANDLING
//start
function startSession(){
    data = {
        'requestType': 0,
        'nVertex': nVertex
    }
    jQuery.post(
        'http://' + ip + ':5200',
        data,
        successStart
    );
}
function successStart(data){
    sessionID = data;
}
//end
function endSession(){
    data = {
        'requestType': -1,
    }
    jQuery.post(
        'http://' + ip + ':5200',
        data
    );
}

// GRAPH PROCESSING
function makeGraph(){
    nVertex = jQuery('#nVertex').val();
    // create an array with nodes
    nodes = new vis.DataSet();
    for (var i = 0; i < nVertex; i++){
        nodes.add({
            id: i,
            label: i.toString(),
            color: '#007bff',
            font: {
                color: '#FFFFFF'
            }
        })
    }
    edges = new vis.DataSet();
    // create a network
    var data = {
        nodes: nodes,
        edges: edges,
    };
    var options = {};
    var network = new vis.Network(container, data, options);

    startSession();
}

function addArc(){
    from = jQuery('#addfrom').val();
    to = jQuery('#addto').val();
    weight = jQuery('#addweight').val();
    edges.add({
        from: from,
        to: to,
        value: weight,
        color: {color: '#000000'},
        arrows: "to" })
    nArcs++;
    var data = {
        nodes: nodes,
        edges: edges,
    };
    var options = {};
    var network = new vis.Network(container, data, options);

    ///*
    data = {
        'requestType': 1,
        'id': sessionID,
        'from': from,
        'to': to,
        'weight': weight
    }
    jQuery.post(
        'http://' + ip + ':5200',
        data,
        success
    );
    //*/
}

function removeArc(){
    from = jQuery('#removefrom').val();
    to = jQuery('#removeto').val();
    edges.forEach(function(item, i) {
        if (item['from'] == from && item['to'] == to){
            edges.remove(item);
        }
    });
    
    var data = {
        nodes: nodes,
        edges: edges,
    };
    var options = {};
    var network = new vis.Network(container, data, options);

    ///*
    data = {
        'requestType': 2,
        'id': sessionID,
        'from': from,
        'to': to
    }
    jQuery.post(
        'http://' + ip + ':5200',
        data,
        success
    );
    //*/
}

function success(data){
    from = jQuery('#addfrom').val('');
    to = jQuery('#addto').val('');
    weight = jQuery('#addweight').val(1);
    from = jQuery('#removefrom').val('');
    to = jQuery('#removeto').val('');
}

function findPath(){
    from = jQuery('#findPathfrom').val();
    to = jQuery('#findPathto').val();

    ///*
    data = {
        'requestType': 3,
        'id': sessionID,
        'from': from,
        'to': to
    }
    jQuery.post(
        'http://' + ip + ':5200',
        data,
        successFindPath
    );
    //*/
}

function successFindPath(data){
    from = jQuery('#findPathfrom').val('');
    to = jQuery('#findPathto').val('');
    console.log(data);
    dataset = JSON.parse(data);

    var delayInMilliseconds = 500; // 1/2 second
    for (var i = 0; i < dataset.length; i++){
        curr = nodes.get(parseInt(dataset[i]));
        nodes.remove(curr);
        curr['color'] = '#FF0000';
        nodes.add(curr);
    }
    var data = {
        nodes: nodes,
        edges: edges,
    };
    var options = {};
    var network = new vis.Network(container, data, options);

    setTimeout(function(dataset) {
        for (var i = 0; i < dataset.length; i++){
            curr = nodes.get(parseInt(dataset[i]));
            nodes.remove(curr);
            curr['color'] = '#007bff';
            nodes.add(curr);
        }
        var data = {
            nodes: nodes,
            edges: edges,
        };
        var options = {};
        var network = new vis.Network(container, data, options);
    }, 7500, dataset);

    //alert(ReceivedData);
}

// Utility functions
function removeItemOnce(arr, value) {
    var index = arr.indexOf(value);
    if (index > -1) {
        arr.splice(index, 1);
    }
    return arr;
}
  
function removeItemAll(arr, value) {
var i = 0;
while (i < arr.length) {
    if (arr[i] === value) {
    arr.splice(i, 1);
    } else {
    ++i;
    }
}
return arr;
}