'use strict';

/**
 * @ngdoc service
 * @name clientApp.account
 * @description
 * # account
 * Service in the clientApp.
 */
angular.module('clientApp')
  .service('Account', function ($q, $http, $timeout, Config, $rootScope) {

    // A private cache key.
    var cache = {};

    // Update event broadcast name.
    var broadcastUpdateEventName = 'ProductivityAccountChange';

    /**
     * Return the promise with the events list, from cache or the server.
     *
     * @returns {*}
     */
    this.get = function() {
      return $q.when(cache.data || getDataFromBackend());
    };

    /**
     * Return events array from the server.
     *
     * @returns {$q.promise}
     */
    function getDataFromBackend() {
      var deferred = $q.defer();
      var url = Config.backend + '/api/me/';

      $http({
        method: 'GET',
        url: url,
        transformResponse: prepareResponse
      }).success(function(response) {
        setCache(response[0]);
        deferred.resolve(response[0]);
      });

      return deferred.promise;
    }

    /**
     * Save meters in cache, and broadcast en event to inform that the meters data changed.
     *
     * @param data
     *   The data to cache.
     */
    var setCache = function(data) {
      // Cache data.
      cache = {
        data: data,
        timestamp: new Date()
      };

      // Clear cache in 60 seconds.
      $timeout(function() {
        cache = {};
      }, 60000);

      // Broadcast a change event.
      $rootScope.$broadcast(broadcastUpdateEventName);
    };

    /**
     * Prepare response; Convert ID to int.
     *
     * As we explicitly require ui-router to match an int, we must case the
     * entity ID to integer.
     *
     * @param data
     *
     * @returns {*}
     */
    function prepareResponse(data) {
      // Convert response serialized to an object.
      data = angular.fromJson(data).data;

      if (!data) {
        // A 401 response was sent.
        return;
      }

      angular.forEach(data[0].companies, function(value, key) {
        data[0].companies[key].id = parseInt(value.id);
      });

      return data;
    }

    $rootScope.$on('clearCache', function() {
      cache = {};
    });

  });
