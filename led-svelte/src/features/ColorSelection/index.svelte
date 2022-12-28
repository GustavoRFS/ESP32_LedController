<script lang="ts">
  import Button from '@smui/button/src/Button.svelte';
  import { Label } from '@smui/common';
  import {HsvPicker} from 'svelte-color-picker'
  import type { Color } from '../../shared/@types/Color';
  import "./index.css"

  let selectedColor:Color={a:1,b:0,g:0,r:255};
  const setSelectedColor=(color:Color)=>{
    selectedColor=color;
  }

  const addToFavorites=()=>{
    const favoriteColors:Color[]=JSON.parse(localStorage.getItem("colors"))??[];

    favoriteColors.push(selectedColor);

    localStorage.setItem("colors",JSON.stringify(favoriteColors));
  }
</script>
   
<div style="display: flex;justify-content:center;flex-direction:column;align-items:center">
  <HsvPicker on:colorChange={(ev)=>setSelectedColor(ev.detail)} />
  <p>
    <Button on:click={addToFavorites} variant="raised" color="secondary"><Label>Adicionar cor aos favoritos</Label></Button>
  </p>
  <p>
    <Button variant="raised" color="secondary"><Label>-</Label></Button>
    Brilho
    <Button variant="raised" color="secondary"><Label>+</Label></Button>
  </p>
  <p>
    <Button variant="raised" color="secondary"><Label>-</Label></Button>
    Velocidade
    <Button variant="raised" color="secondary"><Label>+</Label></Button>
  </p>
</div>