
$(function () {

    //generate main content based on result.js
    var generator = new Generator();

    //set header text as filter id
    document.querySelector("#navbar-header-text").innerHTML += filterOutput[0]["filter-id"];

    //fill the statistics
    var calculator = new Calculator();
    var stats = calculator.getStatistics();

    document.getElementById('stats-total').innerHTML = stats.total;
    document.getElementById('stats-valid').innerHTML = stats.valid;
    document.getElementById('stats-percentage').innerHTML = stats.percentage * 100 + "%";
    document.getElementById('stats-average').innerHTML = stats.average;
    document.getElementById('stats-max').innerHTML = stats.max;
    document.getElementById('stats-min').innerHTML = stats.min;
    document.getElementById('stats-median').innerHTML = stats.median;
    document.getElementById('1/4-Fraction').innerHTML = stats["1/4-Fraction"];

    //insert filter output element
    var elemid = 0;


    filterOutput.forEach((elem) => {
        //generate basic information based on template html
        document.querySelector("#main-content").innerHTML +=
            generator.getElemHTML(elem, 'filter-output-elem-' + elemid);

        //generate popover for every element
        var popOverHTML = generator.getPopoverHTML(elem);

        //apply to popover's content
        var popID = '#filter-output-elem-' + elemid;
        $(popID).attr('data-content', popOverHTML);

        ++elemid;
    });

    $('[data-toggle="popover"]').popover({
        title: 'Details',
        container: 'body',
        trigger: 'hover',
        placement: 'bottom',
        html: true,
    });
})