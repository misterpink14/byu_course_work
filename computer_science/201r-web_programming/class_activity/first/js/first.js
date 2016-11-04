var firstApp = angular.module('firstApp', []);
firstApp.controller('FirstController', function($scope) {
  $scope.first = 'Some';
  $scope.last = 'One';
  $scope.heading = 'Message: ';
  $scope.updateMessage = function() {
	$scope.message = 'Hello ' + 
		$scope.first.toUpperCase() +' '+ 
		$scope.last.toUpperCase() + '!';
  };
  $scope.lowerCase = function(){
	if ($scope.message) {
		$scope.message = $scope.message.toLowerCase()
		}
  }
})