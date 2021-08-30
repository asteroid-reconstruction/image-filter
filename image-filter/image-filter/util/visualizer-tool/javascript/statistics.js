(function (window) {

    function Calculator() {

    }

    Calculator.prototype.getStatistics = function () {
        //basic
        var total = filterOutput.length;
        var valid = 0;

        //min,max,average,median
        var min = Number.MAX_VALUE;
        var max = -Number.MAX_VALUE;
        var med =
            total % 2 == 0 ?
                (filterOutput[total / 2]["final-index"] + filterOutput[total / 2 - 1]["final-index"]) / 2 :
                filterOutput[(total - 1) / 2]["final-index"];
        var sum = 0;
        var count = 0;
        var frac = 0;


        filterOutput.forEach((elem) => {
            if (elem.passed) ++valid;
            var value = elem["final-index"];
            if (min > value) min = value;
            if (max < value) max = value;
            if (count++ == Math.floor(total / 4))
                frac = elem["final-index"];
            sum += value;
        });

        return new Object({
            total: total,
            valid: valid,
            percentage: valid / total,
            min: min,
            max: max,
            median: med,
            average: sum / total,
            "1/4-Fraction": frac,
        });
    }


    window.Calculator = Calculator;

})(window);