import Vue from 'vue'
import './plugins/vuetify'
import App from './App.vue'
import router from './router'
import store from './store'
import * as VueGoogleMaps from 'vue2-google-maps'
import VueFire from 'vuefire'
import firebase from 'firebase'
import {config} from './helpers/firebaseConfig'
Vue.use(VueFire)

Vue.use(VueGoogleMaps, {
  load: {
    key: 'AIzaSyCsm1264u4iBvHrvuCmn5AbHBwD5i1pJ0Y',
    libraries: 'places', // This is required if you use the Autocomplete plugin
  }
})
Vue.config.productionTip = false

new Vue({
  router,
  store,
  created() {
    firebase.initializeApp(config);
    Vue.prototype.$db = firebase.database()
    firebase.auth().onAuthStateChanged((user) => {
      if(user) {
        this.$router.push('/success')
      } else {
        this.$router.push('/auth')
      }
     });
    },
  render: h => h(App)
}).$mount('#app')
