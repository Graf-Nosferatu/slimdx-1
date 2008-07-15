﻿/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

namespace Asteroids
{
    /// <summary>
    /// Represents the player's primary weapon.
    /// </summary>
    class PrimaryWeapon : Weapon
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="PrimaryWeapon"/> class.
        /// </summary>
        /// <param name="game">The game.</param>
        public PrimaryWeapon(Asteroids game)
            : base(game)
        {
            // load the bullet model
            BulletModel = VectorModel.FromFile("Content/Models/PlayerBullet.xml");
            Game.Resources.Add(BulletModel);

            // weapon settings
            CoolDownRate = 8.0f;
            BulletSpeed = 10.0f;
            BulletRotation = 4.0f;
            BulletLife = 75.0f;
            Damage = 100.0f;
        }
    }
}