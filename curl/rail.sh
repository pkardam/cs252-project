curl "https://travel.paytm.com/api/trains/v1/search?client=web&departureDate=20180827&destination=AF&source=CNB" | jq -r  '.["body"]["trains"][] | .trainName + "   " + .duration  +  "    " + .runningOn.fri '