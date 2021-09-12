# image-filter
Dedicated to picking out best images for asteroid reconstruction

## Workflow
A general image filter is provided to be flexible enough for filtering.
You may write your own image quality indicators, add them to the filter, impose a calculation method and invoke ```ImageFilter::filter``` function
to pick out appropriate images for reconstruction.

## Visualization
HTML-based visualization tool is available to visualize the filtering result. Indicator scores of every stage can be found on the local web page. Also, a form of incomplete statistics concerning the result is shown on top of the page.