(function (window) {

    // Return substitute of '{propName}'
    // with propValue in given 'string'
    var insertProperty = function (string, propName, propValue) {
        var propToReplace = "{" + propName + "}";
        string = string.replace(new RegExp(propToReplace, "g"), propValue);
        return string;
    };

    function Generator() {
    }

    //function to generate HTML for every element
    Generator.prototype.getElemHTML = function (filterOutputElem, elemID) {
        //get snippet
        var elemHTML = document.querySelector('#filter-output-elem-template').innerHTML;

        elemHTML = insertProperty(elemHTML,
            'elem-id', String(elemID));

        //get file name from path
        var fileName = filterOutputElem["image-url"];
        fileName = fileName.substring(fileName.lastIndexOf('/') + 1);

        //insert information
        elemHTML = insertProperty(elemHTML,
            'image-url', filterOutputElem["image-url"]);

        elemHTML = insertProperty(elemHTML,
            'image-name', fileName);

        elemHTML = insertProperty(elemHTML,
            'status-sign-url', filterOutputElem["passed"] ? "./resource/passed.png" : "./resource/filtered.png");

        elemHTML = insertProperty(elemHTML,
            'final-index', filterOutputElem["final-index"]);

        return elemHTML;
    }

    //function to generate HTML for pop over of every element
    Generator.prototype.getPopoverHTML = function (filterOutputElem) {
        //get snippet
        var elemPopoverHTML = document.querySelector("#elem-popover-template").innerHTML;

        elemPopoverHTML = insertProperty(elemPopoverHTML,
            'filter-id', filterOutputElem["filter-id"]);

        //generate stage index table
        //var stageTableRowTemplateHTML = document.querySelector('#stage-index-row').innerHTML;
        var stageTableRowTemplateHTML = document.querySelector("#stage-index-row").innerHTML;
        var stageTableAllRowHTML = "";

        for (var i = 0; i < filterOutputElem["indicator-ids"].length; ++i) {
            var rowHTML = stageTableRowTemplateHTML;

            rowHTML = insertProperty(rowHTML,
                'row', i + 1);

            rowHTML = insertProperty(rowHTML,
                'indicator-id', "'" + filterOutputElem["indicator-ids"][i] + "'");

            rowHTML = insertProperty(rowHTML,
                'stage-index', "<br>" + filterOutputElem["stage-indices"][i]);

            stageTableAllRowHTML += rowHTML;
        }

        elemPopoverHTML = insertProperty(elemPopoverHTML,
            'table-rows', stageTableAllRowHTML);

        return elemPopoverHTML;
    }

    //export object constructor
    window.Generator = Generator;
})(window)